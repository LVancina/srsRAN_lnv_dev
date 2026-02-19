/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#pragma once

#include "srsran/asn1/asn1_utils.h"
// #include "srsran/asn1/e2ap/e2sm_kpm.h"
#include "srsran/e2/e2.h"
#include "srsran/e2/e2sm/e2sm.h"
#include "e2sm/e2sm_ni/e2sm_ni_message_prov.h"
// #include "srsran/e2/e2sm/e2sm_kpm.h"
#include <map>

namespace srsran {

class e2sm_ni_impl : public e2sm_interface
{
    public:
    e2sm_ni_impl(srslog::basic_logger& logger_, e2sm_handler& e2sm_packer_, e2sm_ni_message_prov& msg_prov_);

    std::unique_ptr<e2sm_report_service> get_e2sm_report_service(const byte_buffer& action_definition) override;
    // Decode the action_definition
    // Determine the style type for the action
    // Return a unique pointer for that specific service and style

    std::unique_ptr<e2sm_report_service> get_e2sm_insert_service(const byte_buffer& action_definition);
    // Decode the action_definition
    // Determine the style type for the action
    // Return a unique pointer for that specific service and style

    e2sm_control_service* get_e2sm_control_service(const e2sm_ric_control_request& request) override;
    // Decode the action_definition
    // Determine the style type for the action
    // Return a unique pointer for that specific service and style

    // TODO - Add supporting functions

    private:
    srslog::basic_logger&   logger;
    e2sm_handler&           e2sm_packer;
    e2sm_ni_message_prov&   msg_prov;

};

} // namespace srsran

