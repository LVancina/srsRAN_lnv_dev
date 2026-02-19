/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#include "e2sm/e2sm_ni/e2sm_ni_impl.h"
#include "srsran/asn1/asn1_utils.h"

using namespace asn1::e2ap;
using namespace asn1::e2sm_ni;
using namespace srsran;

e2sm_ni_impl::e2sm_ni_impl(srslog::basic_logger&   logger_,
                            e2sm_handler&           e2sm_packer_,
                            e2sm_ni_message_prov& msg_prov_) :
logger(logger_), e2sm_packer(e2sm_packer_), msg_prov(msg_prov_)
{
}

std::unique_ptr<e2sm_report_service> e2sm_ni_impl::get_e2sm_report_service(const byte_buffer& action_definition) {
  e2sm_action_definition action_def = e2sm_packer.handle_packed_e2sm_action_definition(action_definition);
  if (action_def.service_model != e2sm_service_model_t::NI) {
    logger.info("Unknown service model {}", action_def.service_model);
    return nullptr;
  }
  e2_sm_ni_action_definition_s& e2sm_ni_action_def =
      variant_get<e2_sm_ni_action_definition_s>(action_def.action_definition);
  uint32_t ric_style_type = e2sm_ni_action_def.ric_style_type;
  switch (ric_style_type) {
    case 1:
      // Service Style 1: Complete message
      return std::make_unique<e2sm_ni_report_service_style1>(std::move(e2sm_ni_action_def), msg_prov);
    case 2:
      // Service Style 2: Partial message
      return std::make_unique<e2sm_ni_report_service_style2>(std::move(e2sm_ni_action_def), msg_prov);
    default:
      logger.info("Unknown RIC style type %i", ric_style_type);
      return nullptr;
  }
    // Decode the action_definition
    // Determine the style type for the action
    // Return a unique pointer for that specific service and style
}

std::unique_ptr<e2sm_report_service> e2sm_ni_impl::get_e2sm_insert_service(const byte_buffer& action_definition){
    // Decode the action_definition
    // Determine the style type for the action
    // Return a unique pointer for that specific service and style
}

e2sm_control_service* get_e2sm_control_service(const e2sm_ric_control_request& request) {
    // Decode the action_definition
    // Determine the style type for the action
    // Return a unique pointer for that specific service and style
}

// Supporting functions

