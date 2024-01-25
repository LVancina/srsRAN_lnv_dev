/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/cu_cp/cu_cp.h"
#include "srsran/ngap/ngap_configuration.h"
#include <future>

namespace srsran {
namespace srs_cu_cp {

class cu_cp_routine_manager;
class cu_cp_ngap_control_notifier;
class ngap_cu_cp_connection_notifier;

class amf_connection_manager
{
public:
  amf_connection_manager(cu_cp_routine_manager&       routine_manager_,
                         const ngap_configuration&    ngap_cfg_,
                         cu_cp_ngap_control_notifier& ngap_ctrl_notif_);

  /// \brief Initiates the connection to the AMF.
  /// A promise is passed as a parameter to enable blocking synchronization between the completion of the scheduled
  /// async task and the caller side.
  void connect_to_amf(std::promise<bool>* completion_signal = nullptr);

  /// Checks whether the CU-CP is connected to the AMF.
  bool is_amf_connected() const { return amf_connected.load(std::memory_order_relaxed); }

private:
  void handle_connection_setup_result(bool success);

  cu_cp_routine_manager&       routine_manager;
  const ngap_configuration&    ngap_cfg;
  cu_cp_ngap_control_notifier& ngap_ctrl_notifier;

  std::atomic<bool> amf_connected{false};
};

} // namespace srs_cu_cp
} // namespace srsran