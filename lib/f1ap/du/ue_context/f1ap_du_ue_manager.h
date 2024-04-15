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

#include "f1ap_du_ue.h"
#include "srsran/du_high/du_high_executor_mapper.h"
#include <mutex>
#include <unordered_map>

namespace srsran {
namespace srs_du {

/// \brief Stores the list of UE contexts currently registered in the F1AP-DU.
class f1ap_du_ue_manager
{
public:
  f1ap_du_ue_manager(f1ap_du_configurator&       du_handler_,
                     task_executor&              ctrl_exec_,
                     du_high_ue_executor_mapper& ue_exec_mapper_) :
    du_handler(du_handler_), ctrl_exec(ctrl_exec_), ue_exec_mapper(ue_exec_mapper_)
  {
  }

  /// Called when a new connection is established to the CU-CP.
  void update_tx_pdu_notifier(f1ap_message_notifier& f1ap_msg_notifier_) { f1ap_msg_notifier = &f1ap_msg_notifier_; }

  f1ap_du_ue& add_ue(du_ue_index_t ue_index)
  {
    srsran_sanity_check(f1ap_msg_notifier != nullptr, "Creating a UE before a connection to the CU-CP is established");
    srsran_assert(not ues.contains(ue_index), "Duplicate ueId={} detected", ue_index);

    gnb_du_ue_f1ap_id_t f1ap_id = static_cast<gnb_du_ue_f1ap_id_t>(next_gnb_f1ap_du_ue_id++);
    ues.emplace(
        ue_index, ue_index, f1ap_id, du_handler, *f1ap_msg_notifier, ctrl_exec, ue_exec_mapper.ctrl_executor(ue_index));

    {
      std::lock_guard<std::mutex> lock(map_mutex);
      f1ap_ue_id_to_du_ue_id_map[f1ap_id] = ue_index;
    }

    return ues[ue_index];
  }

  bool remove_ue(du_ue_index_t ue_index)
  {
    if (not ues.contains(ue_index)) {
      return false;
    }
    {
      std::lock_guard<std::mutex> lock(map_mutex);
      f1ap_ue_id_to_du_ue_id_map.erase(ues[ue_index].context.gnb_du_ue_f1ap_id);
    }
    ues.erase(ue_index);
    return true;
  }

  f1ap_du_ue&       operator[](du_ue_index_t ue_index) { return ues[ue_index]; }
  const f1ap_du_ue& operator[](du_ue_index_t ue_index) const { return ues[ue_index]; }

  f1ap_du_ue*       find(du_ue_index_t ue_index) { return ues.contains(ue_index) ? &ues[ue_index] : nullptr; }
  const f1ap_du_ue* find(du_ue_index_t ue_index) const { return ues.contains(ue_index) ? &ues[ue_index] : nullptr; }

  f1ap_du_ue* find(gnb_du_ue_f1ap_id_t du_ue_f1ap_id)
  {
    std::lock_guard<std::mutex> lock(map_mutex);
    auto                        it = f1ap_ue_id_to_du_ue_id_map.find(du_ue_f1ap_id);
    return it != f1ap_ue_id_to_du_ue_id_map.end() ? find(it->second) : nullptr;
  }
  const f1ap_du_ue* find(gnb_du_ue_f1ap_id_t du_ue_f1ap_id) const
  {
    std::lock_guard<std::mutex> lock(map_mutex);
    auto                        it = f1ap_ue_id_to_du_ue_id_map.find(du_ue_f1ap_id);
    return it != f1ap_ue_id_to_du_ue_id_map.end() ? find(it->second) : nullptr;
  }
  const f1ap_du_ue* find(gnb_cu_ue_f1ap_id_t ue_cu_f1ap_id) const
  {
    std::lock_guard<std::mutex> lock(map_mutex);
    auto                        it = std::find_if(ues.begin(), ues.end(), [ue_cu_f1ap_id](const f1ap_du_ue& e) {
      return e.context.gnb_cu_ue_f1ap_id == ue_cu_f1ap_id;
    });
    return it != ues.end() ? &*it : nullptr;
  }

  bool contains(du_ue_index_t ue_index) const { return find(ue_index) != nullptr; }
  bool contains(gnb_du_ue_f1ap_id_t du_ue_f1ap_id) const { return find(du_ue_f1ap_id) != nullptr; }

  du_ue_index_t get_ue_index(gnb_du_ue_f1ap_id_t du_ue_f1ap_id) const
  {
    std::lock_guard<std::mutex> lock(map_mutex);
    auto                        it = f1ap_ue_id_to_du_ue_id_map.find(du_ue_f1ap_id);
    return it == f1ap_ue_id_to_du_ue_id_map.end() ? INVALID_DU_UE_INDEX : it->second;
  }

private:
  f1ap_du_configurator&       du_handler;
  f1ap_message_notifier*      f1ap_msg_notifier = nullptr;
  task_executor&              ctrl_exec;
  du_high_ue_executor_mapper& ue_exec_mapper;

  uint64_t next_gnb_f1ap_du_ue_id = 0;

  slotted_array<f1ap_du_ue, MAX_NOF_DU_UES> ues;

  mutable std::mutex                                     map_mutex;
  std::unordered_map<gnb_du_ue_f1ap_id_t, du_ue_index_t> f1ap_ue_id_to_du_ue_id_map;
};

} // namespace srs_du
} // namespace srsran