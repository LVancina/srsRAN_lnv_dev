/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// TODO - refactor this file to match new srsRAN software design
/*******************************************************************************
 *
 *                   3GPP TS ASN1 E2SM NI v15.3.0 (2025-08)
 *
 ******************************************************************************/

#pragma once

#include "../asn1_utils.h"
#include "srsran/asn1/asn1_ap_utils.h"
#include "e2sm_common_ies.h"
#include <cstdint>
#include <cstdio>
#include <stdarg.h>

namespace asn1 {
namespace e2sm {

/*******************************************************************************
 *                             Constant Definitions
 ******************************************************************************/

#define ASN1_E2SM_NI_MAXOF_INT_PROTOCOL_TESTS 15
#define ASN1_E2SM_NI_MAXOF_RAN_UE_GROUPS      255
#define ASN1_E2SM_NI_MAXOF_ACTION_PARAMETERS  255
#define ASN1_E2SM_NI_MAXOF_RAN_PARAMETERS     65535
#define ASN1_E2SM_NI_MAXOF_NI_TYPES           63
// #define ASN1_E2SM_NI_MAXOF_RIC_STYLES         63   // already defined in e2sm_common_ies.h

using gnb_du_id = uint64_t;
using gnb_cu_up_id = uint64_t;
/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/
const uint32_t None = 2147483647;

// ***Already implemented in common IEs***
// GlobalENB-ID ::= SEQUENCE
// struct global_enb_id_s {
//   bool ext = false;
//   std::string plmn_id;
//   enb_id_c enb_id;
//     // ...
//
//   // sequence methods
//   SRSASN_CODE pack(bit_ref& bref) const;
//   SRSASN_CODE unpack(cbit_ref& bref);
//   void        to_json(json_writer& j) const;
// };

// ***Already implemented in common IEs***
//ENB-ID ::= CHOICE
// struct enb_id_c {
//   struct types_opts{
//     enum options{ macro_enb_id, home_enb_id, /*...*/ short_macro_enb_id, 
//       long_macro_enb_id, nulltype};
//     // ***These options will be defined later***
//   };
//   typedef enumerated<types_opts, true> types;
//
//   // Choice methods
//   enb_id_c() = default;
//
//   SRSASN_CODE pack(bit_ref& bref) const;
//   SRSASN_CODE unpack(cbit_ref& bref);
//   void        to_json(json_writer& j) const;
//
// private:
//   types                   type_;
//   choice_buffer_t<real_s> c;
//
//   void destroy_();
// };

// ***Already implemented in common IEs***
// GlobalenGNB-ID ::= SEQUENCE
// struct global_gnb_id_s {
//   bool ext = false;
//   std::string plmn_id;
//   std::string gnb_id;
//   //...
//   
//   // sequence methods
//   SRSASN_CODE pack(bit_ref& bref) const;
//   SRSASN_CODE unpack(cbit_ref& bref);
//   void        to_json(json_writer& j) const;
// };

// TODO - validate AI generated code below
//ENGNB-ID ::= CHOICE
struct engnb_id_c {
  struct types_opts {
    enum options {
      gnb_id, /*...*/ nulltype
    } value;
    const char* to_string() const;
    };
    using types = enumerated<types_opts, true>;

    // choice methods
    types type() const { return type_; }
    SRSASN_CODE pack(bit_ref& bref) const;
    SRSASN_CODE unpack(cbit_ref& bref);
    void        to_json(json_writer& j) const;
    // getters
    bounded_bitstring<22, 32, false, true>&       gnb_id() {
      // assert_choice_type(types::nr_cgi, type_, "CGI");
      assert_choice_type(types::gnb_id, type_, "ENGNG_ID");
      return gnb_id_;
    }
    const bounded_bitstring<22, 32, false, true>& gnb_id() const { return gnb_id_; }

  private:
    types type_;
    bounded_bitstring<22, 32, false, true> gnb_id_;
  };

  //PLMN-Identity ::= OCTET STRING (SIZE(3))
    // Type fixed_octstring
    // Will be directly defined in the structures it is part of.

  //GNB-CU-UP-ID::= INTEGER (0..68719476735)
    // Type uint64
    // Will be directly defined in the structures it is part of.

  //GNB-DU-ID::= INTEGER (0..68719476735)
    // Type uint64
    // Will be directly defined in the structures it is part of.

  struct globalgnb_id_s {
    bool                     ext = true;
    fixed_octstring<3, true> plmn_id;
    gnb_id_c                 gnb_id;
    // ...

    // sequence methods
    SRSASN_CODE pack(bit_ref& bref) const;
    SRSASN_CODE unpack(cbit_ref& bref);
    void        to_json(json_writer& j) const;
  };

  // GNB-ID-Choice ::= CHOICE
    // Already implemented in common IEs

  // GlabalngeNB-ID ::= SEQUENCE
  struct globalng_enb_id_s {
    bool ext = true;
    fixed_octstring<3, true> plmn_id;
    enb_id_c enb_id;

    // sequence methods
    SRSASN_CODE pack(bit_ref& bref) const;
    SRSASN_CODE unpack(cbit_ref& bref);
    void        to_json(json_writer& j) const;
  };

  // ENG-ID-Choice ::= CHOICE
    // Already implemented in common IEs

  // GlobalNG-RANNode-ID ::= CHOICE
    // Already implemented in common IEs as global_ng_ran_node_id_c
    //

struct criticality_opts {
  enum options {reject, ignore, notify} values;
  const char* to_string() const;
};
using criticality_e = enumerated<criticality_opts, false>;

struct presence_opts {
  enum options {optional, conditional, mandatory} values;
  const char* to_string() const;
};
using presence_e = enumerated<presence_opts, false>;

using procedure_code = uint8_t;
   
using protocol_ie_id = uint64_t;

   
// ****************************************************************************
// E2SM-NI Service Model IEs
// ****************************************************************************

// ----------------------------------------------------------------------------
// Common IEs
// ----------------------------------------------------------------------------

// RANparameter-ID ::= INTEGER (0..maxofRANparameters)
using ran_param_id = uint8_t;

// RANparameter-Value ::= CHOICE
struct ran_param_value_c {
  struct types_opts {
    enum options {
      value_int,
      value_enum,
      value_bool,
      value_bits,
      value_octs,
      value_prts,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  
  //getters
  uint64_t value_int() {
    assert_choice_type(types::value_int, type_, "RANParameter-Value");
    return value_int_;
  }

  uint64_t value_enum() {
    assert_choice_type(types::value_enum, type_, "RANParameter-Value");
    return value_enum_;
  }

  uint64_t value_bool() {
    assert_choice_type(types::value_bool, type_, "RANParameter-Value");
    return value_bool_;
  }

  unbounded_bitstring<true, true> value_bits() {
    assert_choice_type(types::value_bits, type_, "RANParameter-Value");
    return value_bits_;
  }

  unbounded_octstring<true> value_octs() {
    assert_choice_type(types::value_octs, type_, "RANParameter-Value");
    return value_octs_;
  }

  printable_string<1, 150, true, true> value_prts() {
    assert_choice_type(types::value_prts, type_, "RANParameter-Value");
    return value_prts_;
  }

  private:
  types type_;
  uint64_t value_int_;
  uint64_t value_enum_;
  bool value_bool_;
  unbounded_bitstring<true, true> value_bits_;
  unbounded_octstring<true> value_octs_;
  printable_string<1, 150, true, true> value_prts_;
};

struct ran_param_item_s {
  bool ext = true;
  ran_param_id ran_param_id;
  ran_param_value_c ran_param_value;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};


// ----------------------------------------------------------------------------
// Event Trigger Definition
// ----------------------------------------------------------------------------
using int_protocol_ie_l = dyn_array<ni_protocol_ie_item>;
  struct e2sm_ni_event_trigger_format1_s {
    bool ext = true;
    ni_type int_type;
    ni_identifier int_id;
    ni_direction int_direction;
    ni_message_type int_message_type;

    bool protocol_ie_list_present = false;
    int_protocol_ie_l int_protocol_ie_list;

    // sequence methods
    SRSASN_CODE pack(bit_ref& bref) const;
    SRSASN_CODE unpack(cbit_ref& bref);
    void        to_json(json_writer& j) const;
  };

  // E2SM-NI EventTriggerDefinition IE
  struct e2sm_ni_event_trigger_definition_c {
    struct types_opts {
      enum options {event_definition_format1, /*...*/ nulltype} values;
      const char* to_string() const;
    };
    using types = enumerated<types_opts, true>;

    // choice methods
    types type() const { return type_; }
    SRSASN_CODE pack(bit_ref& bref) const;
    SRSASN_CODE unpack(cbit_ref& bref);
    void        to_json(json_writer& j) const;
    //getters
    e2sm_ni_event_trigger_format1_s& event_definition_format1() {
    assert_choice_type(types::event_definition_format1, type_, "E2SM-NI Event Trigger Definition");
    return format1;
    }
    
    private:
    types type_;
    e2sm_ni_event_trigger_format1_s format1;
  };

// ----------------------------------------------------------------------------
// Action Definition
// ----------------------------------------------------------------------------
using action_param_l = dyn_array<ran_param_item_s>;
struct e2sm_ni_action_definition_format1_s {
  bool ext = true;
  bool action_param_list_present = false;
  action_param_l action_param_list;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

using ran_ue_group_l = dyn_array<ran_ue_group_item_s>;

struct e2sm_ni_action_definition_format2_s {
  bool ext = true;
  bool ran_ue_group_list_present = false;
  ran_ue_group_l ran_ue_group_list;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

struct e2sm_ni_action_definition_format_c {
    struct types_opts {
      enum options {
        action_definition_format1,
        action_definition_format2,
        /*...*/
        nulltype
      } values;
      const char* to_string() const;
    };
    using types = enumerated<types_opts, true>;

    // choice methods
    types type() const { return type_; }
    SRSASN_CODE pack(bit_ref& bref) const;
    SRSASN_CODE unpack(cbit_ref& bref);
    void        to_json(json_writer& j) const;
    //getters
    e2sm_ni_action_definition_format1_s& action_definition_format1() {
      assert_choice_type(types::action_definition_format1, type_, "E2SM-NI Action Definition Format 1");
      return format1;
    }
    e2sm_ni_action_definition_format2_s& action_definition_format2() {
      assert_choice_type(types::action_definition_format2, type_, "E2SM-NI Action Definition Format 2");
      return format2;
    }
    
    private:
    types type_;
    e2sm_ni_action_definition_format1_s format1;
    e2sm_ni_action_definition_format2_s format2;
};

struct e2sm_ni_action_definition_s {
  bool ext = true;
  int64_t ric_style_type = 0;   // TODO - Check if this is correct
  e2sm_ni_action_definition_format_c action_definition_format;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

// ----------------------------------------------------------------------------
// Indication Header
// ----------------------------------------------------------------------------
struct e2sm_ni_indication_header_format1_s {
  bool ext = true;
  ni_type int_type;
  ni_identifier int_id;
  ni_direction int_direction;
  bool time_stamp_present = false;
  ni_time_stamp time_stamp;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

struct e2sm_ni_indication_header_c {
  struct types_opts {
    enum options {
      indication_header_format1,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  e2sm_ni_indication_header_format1_s& indication_header_format1() {
    assert_choice_type(types::indication_header_format1, type_, "E2SM-NI Indication Header");
    return format1;
  }
  private:
  types type_;
  e2sm_ni_indication_header_format1_s format1;
};

// ni_message placeholder
using ni_message = unbounded_octstring<true>;

// ----------------------------------------------------------------------------
// Indication Message
// ----------------------------------------------------------------------------
struct e2sm_ni_indication_message_format1_s {
  bool ext = true;
  ni_message int_message;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

struct e2sm_ni_indication_message_c {
  struct types_opts {
    enum options {
      indication_message_format1,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  e2sm_ni_indication_message_format1_s& indication_message_format1() {
    assert_choice_type(types::indication_message_format1, type_, "E2SM-NI Indication Message");
    return format1;
  }
  private:
  types type_;
  e2sm_ni_indication_message_format1_s format1;
};

// ----------------------------------------------------------------------------
// Call Process ID
// ----------------------------------------------------------------------------
struct e2sm_ni_call_process_format1_s {
  bool ext = true;
  int64_t ran_call_process_id_number = 0;   // TODO - verify this number

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

struct e2sm_ni_call_process_format2_s {
  bool ext = true;
  // std::string ran_call_process_id_number;
  ran_call_process_id_string ran_call_process_id_number;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

struct e2sm_ni_call_process_id_c {
  struct types_opts {
    enum options {
      call_process_format1,
      call_process_format2,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  e2sm_ni_call_process_format1_s& call_process_format1() {
    assert_choice_type(types::call_process_format1, type_, "E2SM-NI Call Process ID");
    return format1;
  }
  e2sm_ni_call_process_format2_s& call_process_format2() {
    assert_choice_type(types::call_process_format2, type_, "E2SM-NI Call Process ID");
    return format2;
  }
  private:
  types type_;
  e2sm_ni_call_process_format1_s format1;
  e2sm_ni_call_process_format2_s format2;
};

// ----------------------------------------------------------------------------
// Control Header
// ----------------------------------------------------------------------------
struct e2sm_ni_control_header_format1_s {
  bool ext = true;

  ni_type int_type;
  ni_identifier int_id;
  ni_direction int_direction;
  ric_ctrl_msg_pri ric_cntl_msg_pri;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;

};

struct e2sm_ni_control_header_c {
  struct types_opts {
    enum options {
      control_header_format1,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  e2sm_ni_control_header_format1_s& control_header_format1() {
    assert_choice_type(types::control_header_format1, type_, "E2SM-NI Control Header");
    return format1;
  }
  private:
  types type_;
  e2sm_ni_control_header_format1_s format1;
};

// ----------------------------------------------------------------------------
// Control Message
// ----------------------------------------------------------------------------
struct e2sm_ni_control_message_format1_s {
  bool ext = true;

  ni_message int_message;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

struct e2sm_ni_control_message_c {
  struct types_opts {
    enum options {
      control_message_format1,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  e2sm_ni_control_message_format1_s& control_message_format1() {
    assert_choice_type(types::control_message_format1, type_, "E2SM-NI Control Header");
    return format1;
  }
  private:
  types type_;
  e2sm_ni_control_message_format1_s format1;
};

// ----------------------------------------------------------------------------
// Control Outcome
// ----------------------------------------------------------------------------
using outcome_element_l = dyn_array<ran_param_item>;

struct e2sm_ni_control_outcome_format1_s {
  bool ext = true;

  bool outcome_element_list_present = false;
  outcome_element_l outcome_element_list;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;

};

struct e2sm_ni_control_outcome_c {
  struct types_opts {
    enum options {
      control_outcome_format1,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  e2sm_ni_control_outcome_format1_s& control_outcome_format1() {
    assert_choice_type(types::control_outcome_format1, type_, "E2SM-NI Control Header");
    return format1;
  }
  private:
  types type_;
  e2sm_ni_control_outcome_format1_s format1;
};

// ----------------------------------------------------------------------------
// RAN Function Description
// ----------------------------------------------------------------------------

using ric_event_trigger_style_l = dyn_array<ric_event_trigger_style_list_s>;
using ric_event_report_style_l = dyn_array<ric_event_report_style_list_s>;
using ric_event_inster_style_l = dyn_array<ric_event_insert_style_list_s>;
using ric_event_control_sytle_l = dyn_array<ric_event_control_style_list_s>;
using ric_event_policy_style_l = dyn_array<ric_event_policy_style_list_s>;

struct e2sm_ni_ran_function_item_s {
  bool ext = true;

  bool ric_event_trigger_style_list_present = false;
  ric_event_trigger_style_l ric_event_trigger_style_list;
  bool ric_event_report_style_list_present = false;
  ric_event_report_style_l ric_event_report_style_list;
  bool ric_event_insert_style_list_present = false;
  ric_event_inster_style_l ric_event_insert_style_list;
  bool ric_event_control_style_list_present = false;
  ric_event_control_sytle_l ric_event_control_style_list;
  bool ric_event_policy_style_list_present = false;
  ric_event_policy_style_l ric_event_policy_style_list;
};

using ni_type_l = dyn_array<e2sm_ni_ran_function_item_s>;
struct e2sm_ni_ran_function_description_s {
  bool ext = true;

  ran_function_name_s ran_function_name;
  bool ni_type_list_present = false;
  ni_type_l ni_type_list;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

// ----------------------------------------------------------------------------
// Common IEs
// ----------------------------------------------------------------------------

// Global-eNB-ID ::= GlobalENB-ID
using global_enb_id = global_enb_id_s;

// Global-en-gNB-ID ::= GlobalenGNB-ID
using global_en_gnb_id = globalen_gnb_id_s;

struct global_gnb_du_id_s {
  bool ext = false;
  global_ng_ran_id global_ng_ran_id;
  gnb_du_id gnb_du_id;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

using global_ng_ran_id = global_ng_ran_node_id_c;
struct global_gnb_cu_up_id_s {
  bool ext = false;
  global_ng_ran_id global_ng_ran_id;
  gnb_cu_up_id gnb_cu_up_id;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

// ***EXAMPLE from common_ies.h***
// NRFrequencyShift7p5khz ::= ENUMERATED
// struct nr_freq_shift7p5khz_opts {
//   enum options { false_value, true_value, /*...*/ nulltype } value;
//
//   const char* to_string() const;
// };
// using nr_freq_shift7p5khz_e = enumerated<nr_freq_shift7p5khz_opts, true>;
//
struct ni_direction_opts {
  enum options {incoming, outgoing, both, /*...*/ nulltype} value;
  const char* to_string() const;
};
using ni_direction_e = enumerated<ni_direction_opts, true>;

struct ni_identifier_c {
  struct types_opts {
    enum options {
      global_enb_id,
      global_en_gnb_id,
      global_ng_ran_id,
      global_gnb_du_id,
      global_gnb_cu_up_id,
      /*...*/
      nulltype
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  ni_identifier_c& global_enb_id() {
    assert_choice_type(types::global_enb_id, type_, "NI Identifier");
    return global_enb_id;
  }
  ni_identifier_c& global_en_gnb_id() {
    assert_choice_type(types::global_en_gnb_id, type_, "NI Identifier");
    return global_en_gnb_id;
  }
  ni_identifier_c& global_ng_ran_id() {
    assert_choice_type(types::global_ng_ran_id, type_, "NI Identifier");
    return global_en_gnb_id;
  }
  ni_identifier_c& global_gnb_du_id() {
    assert_choice_type(types::global_gnb_du_id, type_, "NI Identifier");
    return global_gnb_du_id;
  }
  ni_identifier_c& global_gnb_cu_up_id() {
    assert_choice_type(types::global_gnb_cu_up_id, type_, "NI Identifier");
    return global_gnb_cu_up_id;
  }
private:
  global_enb_id global_enb_id;
  global_en_gnb_id global_en_gnb_id;
  global_ng_ran_id global_ng_ran_id;
  global_gnb_du_id_s global_gnb_du_id;
  global_gnb_cu_up_id_s global_gnb_cu_up_id;
};

// NI-Message ::= OCTET STRING
// Declared above!

// TypeOfMessage ::= ENUMERATED
struct type_of_message_opts {
  enum options {nothing, initiating_message, successful_outcome, unsuccessful_outcome} value;
  const char* to_string() const;
};
using type_of_message_e = enumerated<type_of_message_opts, false>;

struct ni_message_type_approach1_s {
  bool ext = true;
  procedure_code procedure_code;
  type_of_message_e type_of_message;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

using ni_message_type_s1 = ni_message_type_approach1_s;
using ni_message_type_x2 = ni_message_type_approach1_s;
using ni_message_type_ng = ni_message_type_approach1_s;
using ni_message_type_xn = ni_message_type_approach1_s;
using ni_message_type_f1 = ni_message_type_approach1_s;
using ni_message_type_e1 = ni_message_type_approach1_s;

struct ni_message_type_c {
  e1_message_type_s e1_message_type;
};

using ni_protocol_ie_id = protocol_ie_id;

struct ni_protocol_ie_test_opts {
  enum options {equal, greaterthan, lessthan, contains, present, /*...*/ nullvalue} value;
  const char* to_string() const;
};
using ni_protocol_ie_test_e = enumerated<ni_protocol_ie_test_opts, false>;

struct ni_protocol_ie_value_c {
  struct types_opts {
    enum options {
      value_int,
      value_enum,
      value_bool,
      value_bits,
      value_octs,
      value_prts,
      /*...*/
      nullvalue
    } values;
    const char* to_string() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods
  types type() const { return type_; }
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
  //getters
  uint64_t& value_int() {
    assert_choice_type(types::value_int, type_, "NI-ProtocolIE-Value");
    return value_int;
  }
  uint64_t& value_enum() {
    assert_choice_type(types::value_enum, type_, "NI-ProtocolIE-Value");
    return value_enum;
  }
  bool& value_bool() {
    assert_choice_type(types::value_bool, type_, "NI-ProtocolIE-Value");
    return value_bool;
  }
  unbounded_bitstring<true, true>& value_bits() {
    assert_choice_type(types::value_bits, type_, "NI-ProtocolIE-Value");
    return value_bits;
  }
  unbounded_octstring<true>& value_octs() {
    assert_choice_type(types::value_octs, type_, "NI-ProtocolIE-Value");
    return value_octs;
  }
  printable_string<1, 150, true, true>& value_prts() {
    assert_choice_type(types::value_prts, type_, "NI-ProtocolIE-Value");
    return value_prts;
  }
private:
  types type_;
  uint64_t value_int;
  uint64_t value_enum;
  bool value_bool;
  unbounded_bitstring<true, true> value_bits;
  unbounded_octstring<true> value_octs;
  printable_string<1, 150, true, true> value_prts;
};

struct ni_protocol_ie_item_s {
  bool ext = true;
  ni_protocol_ie_id interface_protocol_ie_id;
  ni_protocol_ie_test_e interface_protocol_ie_test;
  in_protocol_ie_value_c interface_protocol_ie_value;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

} // namespace e2sm
} // namespace asn1

