/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#include "e2sm_ni_asn1_packer.h"

using namespace asn1::e2ap;
using namespace asn1::e2sm_ni;
using namespace srsran;

const std::string e2sm_ni_asn1_packer::short_name       = "ORAN-E2SM-NI";
// This oid is made up. Need to verify if it is legitimate or not.
const std::string e2sm_ni_asn1_packer::oid              = "1.3.6.1.4.1.53148.1.2.1.4";
// const std::string e2sm_kpm_asn1_packer::oid              = "1.3.6.1.4.1.53148.1.2.2.2";
// const std::string e2sm_rc_asn1_packer::oid              = "1.3.6.1.4.1.53148.1.1.2.3";
const std::string e2sm_ni_asn1_packer::func_description = "NETWORK INTERFACE";
const uint32_t    e2sm_ni_asn1_packer::ran_func_id      = 4;
const uint32_t    e2sm_ni_asn1_packer::revision         = 0;

e2sm_ni_asn1_packer::e2sm_ni_asn1_packer(e2sm_ni_message_prov& msg_prov_) : msg_prov(msg_prov_) {}

bool e2sm_ni_asn1_packer::add_e2sm_control_service(e2sm_control_service* control_service)
{
  control_services.emplace(control_service->get_style_type(), control_service);
  return true;
}

e2sm_action_definition
e2sm_ni_asn1_packer::handle_packed_e2sm_action_definition(const srsran::byte_buffer& action_definition)
{
  e2sm_action_definition action_def;
  action_def.service_model = e2sm_service_model_t::NI;
  asn1::cbit_ref bref(action_definition);
  // if (variant_get<asn1::e2sm_ni::e2_sm_ni_action_definition_s>(action_def.action_definition).unpack(bref) !=
  if (variant_get<e2_sm_ni_action_definition_s>(action_def.action_definition).unpack(bref) !=
      asn1::SRSASN_SUCCESS) {
    printf("Failed to unpack E2SM NI Action Definition\n");
  }
  return action_def;
}

