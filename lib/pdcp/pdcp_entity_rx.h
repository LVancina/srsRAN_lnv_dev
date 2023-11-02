/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "pdcp_bearer_logger.h"
#include "pdcp_entity_tx_rx_base.h"
#include "pdcp_interconnect.h"
#include "pdcp_pdu.h"
#include "pdcp_rx_metrics_impl.h"
#include "srsran/adt/byte_buffer.h"
#include "srsran/adt/byte_buffer_chain.h"
#include "srsran/pdcp/pdcp_config.h"
#include "srsran/pdcp/pdcp_rx.h"
#include "srsran/support/sdu_window.h"
#include "srsran/support/timers.h"
#include "fmt/format.h"

namespace srsran {

/// PDCP RX state variables,
/// TS 38.323, section 7.1
struct pdcp_rx_state {
  /// RX_NEXT indicates the COUNT value of the next PDCP SDU expected to be received.
  uint32_t rx_next;
  /// RX_DELIV indicates the COUNT value of the first PDCP SDU not delivered to the upper layers, but still
  /// waited for.
  uint32_t rx_deliv;
  /// RX_REORD indicates the COUNT value following the COUNT value associated with the PDCP Data PDU which
  /// triggered t-Reordering.
  uint32_t rx_reord;
};

struct pdcp_rx_sdu_info {
  byte_buffer sdu   = {};
  uint32_t    count = {};
};

/// Base class used for receiving PDCP bearers.
/// It provides interfaces for the PDCP bearers, for the higher and lower layers
class pdcp_entity_rx final : public pdcp_entity_tx_rx_base,
                             public pdcp_rx_status_provider,
                             public pdcp_rx_lower_interface,
                             public pdcp_rx_upper_control_interface,
                             public pdcp_rx_metrics
{
public:
  pdcp_entity_rx(uint32_t                        ue_index,
                 rb_id_t                         rb_id_,
                 pdcp_rx_config                  cfg_,
                 pdcp_rx_upper_data_notifier&    upper_dn_,
                 pdcp_rx_upper_control_notifier& upper_cn_,
                 timer_factory                   timers);

  void handle_pdu(byte_buffer_chain buf) override;

  /// \brief Triggers re-establishment as specified in TS 38.323, section 5.1.2
  void reestablish(security::sec_128_as_config sec_cfg_) override;

  // Rx/Tx interconnect
  void set_status_handler(pdcp_tx_status_handler* status_handler_) { status_handler = status_handler_; }

  /// \brief Compiles a PDCP status report
  ///
  /// Ref: TS 38.323, Sec. 5.4.1, Sec. 6.2.3.1 and Sec. 6.3.{9,10}
  ///
  /// \return Control PDU for PDCP status report as a byte_buffer
  byte_buffer compile_status_report() override;

  /*
   * Header helpers
   */

  /// \brief Reads the header of a PDCP data PDU and writes the content into an associated object
  /// \param[out] hdr Reference to a pdcp_data_pdu_header that is filled with the header content
  /// \param[in] buf Reference to the PDU bytes
  /// \return True if header was read successfully, false otherwise
  bool read_data_pdu_header(pdcp_data_pdu_header& hdr, const byte_buffer_chain& buf) const;
  void discard_data_header(byte_buffer& buf) const;
  void extract_mac(byte_buffer& buf, security::sec_mac& mac) const;

  /*
   * Security configuration
   */
  void configure_security(security::sec_128_as_config sec_cfg_) final
  {
    srsran_assert((is_srb() && sec_cfg_.domain == security::sec_domain::rrc) ||
                      (is_drb() && sec_cfg_.domain == security::sec_domain::up),
                  "Invalid sec_domain={} for {} in {}",
                  sec_cfg.domain,
                  rb_type,
                  rb_id);
    // The 'NULL' integrity protection algorithm (nia0) is used only for SRBs and for the UE in limited service mode,
    // see TS 33.501 [11] and when used for SRBs, integrity protection is disabled for DRBs. In case the ′NULL'
    // integrity protection algorithm is used, 'NULL' ciphering algorithm is also used.
    // Ref: TS 38.331 Sec. 5.3.1.2
    if ((sec_cfg_.integ_algo == security::integrity_algorithm::nia0) &&
        (is_drb() || (is_srb() && sec_cfg_.cipher_algo != security::ciphering_algorithm::nea0))) {
      logger.log_error(
          "Integrity algorithm NIA0 is only permitted for SRBs configured with NEA0. is_srb={} NIA{} NEA{}",
          is_srb(),
          sec_cfg_.integ_algo,
          sec_cfg_.cipher_algo);
    }

    sec_cfg = sec_cfg_;
    logger.log_info(
        "Security configured: NIA{} NEA{} domain={}", sec_cfg.integ_algo, sec_cfg.cipher_algo, sec_cfg.domain);
    if (sec_cfg.k_128_int.has_value()) {
      logger.log_info(sec_cfg.k_128_int.value().data(), 16, "128 K_int");
    }
    logger.log_info(sec_cfg.k_128_enc.data(), 16, "128 K_enc");
  }

  void set_integrity_protection(security::integrity_enabled integrity_enabled_) final
  {
    if (integrity_enabled_ == security::integrity_enabled::on) {
      if (!sec_cfg.k_128_int.has_value()) {
        logger.log_error("Cannot enable integrity protection: Integrity key is not configured.");
        return;
      }
      if (!sec_cfg.integ_algo.has_value()) {
        logger.log_error("Cannot enable integrity protection: Integrity algorithm is not configured.");
        return;
      }
    }
    integrity_enabled = integrity_enabled_;
    logger.log_info("Set integrity_enabled={}", integrity_enabled);
  }
  void set_ciphering(security::ciphering_enabled ciphering_enabled_) final
  {
    ciphering_enabled = ciphering_enabled_;
    logger.log_info("Set ciphering_enabled={}", ciphering_enabled);
  }

  /*
   * Testing Helpers
   */
  void                        set_state(pdcp_rx_state st_) { st = st_; }
  pdcp_rx_state               get_state() { return st; }
  security::sec_128_as_config get_sec_config() { return sec_cfg; }
  bool                        is_reordering_timer_running() { return reordering_timer.is_running(); }

private:
  pdcp_bearer_logger   logger;
  const pdcp_rx_config cfg;

  security::sec_128_as_config  sec_cfg           = {};
  security::security_direction direction         = security::security_direction::uplink;
  security::integrity_enabled  integrity_enabled = security::integrity_enabled::off;
  security::ciphering_enabled  ciphering_enabled = security::ciphering_enabled::off;

  pdcp_rx_state st = {};

  /// Rx window
  std::unique_ptr<sdu_window<pdcp_rx_sdu_info>> rx_window;

  /// Rx reordering timer
  unique_timer reordering_timer;
  class reordering_callback;
  void handle_t_reordering_expire();

  // Handling of different PDU types

  /// \brief Handles a received data PDU.
  /// \param buf The data PDU to be handled (including header and payload)
  void handle_data_pdu(byte_buffer_chain buf);

  /// \brief Handles a received control PDU.
  /// \param buf The control PDU to be handled (including header and payload)
  void handle_control_pdu(byte_buffer_chain buf);

  void deliver_all_consecutive_counts();
  void deliver_all_sdus();
  void discard_all_sdus();

  bool        integrity_verify(byte_buffer_view buf, uint32_t count, const security::sec_mac& mac);
  byte_buffer cipher_decrypt(byte_buffer_chain::const_iterator msg_begin,
                             byte_buffer_chain::const_iterator msg_end,
                             uint32_t                          count);

  /*
   * Notifiers and handlers
   */
  pdcp_tx_status_handler*         status_handler = nullptr;
  pdcp_rx_upper_data_notifier&    upper_dn;
  pdcp_rx_upper_control_notifier& upper_cn;

  timer_factory timers;

  /// Creates the rx_window according to sn_size
  /// \param sn_size Size of the sequence number (SN)
  /// \return unique pointer to rx_window instance
  std::unique_ptr<sdu_window<pdcp_rx_sdu_info>> create_rx_window(pdcp_sn_size sn_size_);

  void log_state(srslog::basic_levels level) { logger.log(level, "RX entity state. {}", st); }
};

// Reordering callback (t-Reordering)
class pdcp_entity_rx::reordering_callback
{
public:
  explicit reordering_callback(pdcp_entity_rx* parent_) : parent(parent_) {}
  void operator()(timer_id_t timer_id);

private:
  pdcp_entity_rx* parent;
};
} // namespace srsran

namespace fmt {
template <>
struct formatter<srsran::pdcp_rx_state> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const srsran::pdcp_rx_state& st, FormatContext& ctx) -> decltype(std::declval<FormatContext>().out())
  {
    return format_to(ctx.out(), "rx_next={} rx_deliv={} rx_reord={}", st.rx_next, st.rx_deliv, st.rx_reord);
  }
};

} // namespace fmt
