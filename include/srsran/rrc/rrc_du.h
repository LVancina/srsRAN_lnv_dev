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

#include "rrc_cell_context.h"
#include "rrc_ue.h"
#include "srsran/ran/band_helper.h"

namespace srsran {

namespace srs_cu_cp {

struct rrc_cell_info {
  nr_band                      band;
  std::vector<rrc_meas_timing> meas_timings;
};

class rrc_du_cell_manager
{
public:
  rrc_du_cell_manager()          = default;
  virtual ~rrc_du_cell_manager() = default;

  virtual bool handle_served_cell_list(const std::vector<cu_cp_du_served_cells_item>& served_cell_list) = 0;
};

struct rrc_ue_creation_message {
  ue_index_t                        ue_index;
  rnti_t                            c_rnti;
  rrc_cell_context                  cell;
  rrc_pdu_f1ap_notifier*            f1ap_pdu_notifier;
  byte_buffer                       du_to_cu_container;
  rrc_ue_task_scheduler*            ue_task_sched;
  optional<rrc_ue_transfer_context> rrc_context;
};

/// \brief Interface class to the main RRC DU object to manage RRC UEs.
/// This interface provides functions to add, remove and release UEs.
class rrc_du_ue_repository
{
public:
  rrc_du_ue_repository()          = default;
  virtual ~rrc_du_ue_repository() = default;

  /// Creates a new RRC UE object and returns a handle to it.
  virtual rrc_ue_interface* add_ue(up_resource_manager& resource_mng, const rrc_ue_creation_message& msg) = 0;

  /// Get a RRC UE object.
  virtual rrc_ue_interface* find_ue(ue_index_t ue_index) = 0;

  /// Send RRC Release to all UEs connected to this DU.
  virtual void release_ues() = 0;
};

/// Handle RRC UE removal
class rrc_ue_removal_handler
{
public:
  virtual ~rrc_ue_removal_handler() = default;

  /// Remove a RRC UE object.
  /// \param[in] ue_index The index of the UE object to remove.
  virtual void remove_ue(ue_index_t ue_index) = 0;
};

/// \brief Interface to query statistics from the RRC DU interface.
class rrc_du_statistics_handler
{
public:
  virtual ~rrc_du_statistics_handler() = default;

  /// \brief Get the number of UEs registered at the RRC DU.
  /// \return The number of UEs.
  virtual size_t get_nof_ues() const = 0;
};

/// Combined entry point for the RRC DU handling.
class rrc_du_interface : public rrc_du_cell_manager,
                         public rrc_du_ue_repository,
                         public rrc_ue_removal_handler,
                         public rrc_du_statistics_handler
{
public:
  virtual ~rrc_du_interface() = default;

  virtual rrc_du_cell_manager&       get_rrc_du_cell_manager()       = 0;
  virtual rrc_du_ue_repository&      get_rrc_du_ue_repository()      = 0;
  virtual rrc_ue_removal_handler&    get_rrc_ue_removal_handler()    = 0;
  virtual rrc_du_statistics_handler& get_rrc_du_statistics_handler() = 0;
};

} // namespace srs_cu_cp

} // namespace srsran
