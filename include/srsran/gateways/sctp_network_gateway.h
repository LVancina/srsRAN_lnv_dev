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

#include "srsran/adt/optional.h"
#include "srsran/gateways/network_gateway.h"
#include "srsran/srslog/srslog.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace srsran {

constexpr uint16_t NGAP_PPID = 60; // NGAP PPID, see TS 38.412, section 7.

/// \brief Configuration for SCTP network gateway
struct sctp_network_gateway_config : common_network_gateway_config {
  std::string connection_name;
  std::string connect_address;
  int         connect_port = 0;
  int         ppid         = 0; /// the Payload Protocol Identifier
  // SCTP specific options
  optional<int32_t> rto_initial;
  optional<int32_t> rto_min;
  optional<int32_t> rto_max;
  optional<int32_t> init_max_attempts;
  optional<int32_t> max_init_timeo;
};

/// \brief Interface to inject PDUs into gateway entity.
class sctp_network_gateway_data_handler
{
public:
  virtual ~sctp_network_gateway_data_handler() = default;

  /// \brief Handle the incoming PDU.
  /// \param[in]  put Byte-buffer with new PDU.
  virtual void handle_pdu(const byte_buffer& pdu) = 0;
};

/// Interface to trigger bind/listen/connect operations on gateway socket.
class sctp_network_gateway_controller : public network_gateway_controller
{
public:
  virtual ~sctp_network_gateway_controller() = default;

  /// \brief Create and connect socket to given address.
  virtual bool create_and_connect() = 0;

  /// \brief Recreate a formerly closed socket and reconnect to a known address and port.
  virtual bool recreate_and_reconnect() = 0;

  /// \brief Start listening on socket.
  virtual bool listen() = 0;
};

/// Interface to inform upper layers about connection establishment, drops, etc.
class sctp_network_gateway_control_notifier
{
public:
  virtual ~sctp_network_gateway_control_notifier() = default;

  /// \brief This callback is invoked when connect() succeeds (client) or a new client connected to a listening socket
  /// (server).
  virtual void on_connection_established() = 0;

  /// \brief This callback is invoked when the connection is dropped or cannot be established in the first place.
  virtual void on_connection_loss() = 0;
};

class sctp_network_gateway : public sctp_network_gateway_controller, public sctp_network_gateway_data_handler
{};

} // namespace srsran
