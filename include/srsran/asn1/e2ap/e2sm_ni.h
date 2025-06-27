/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

/*******************************************************************************
 *
 *                   3GPP TS ASN1 E2SM ni v15.3.0 (2019-03)
 *
 ******************************************************************************/

#pragma once

#include "../asn1_utils.h"
#include <cstdio>
#include <stdarg.h>

namespace asn1 {

namespace e2sm_ni {

/*******************************************************************************
 *                             Constant Definitions
 ******************************************************************************/



/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/
const uint32_t None = 2147483647;

// E2SM-KPM-ActionDefinition-Format1 ::= SEQUENCE
// Format1 is for full messages.
struct e2_sm_ni_action_definition_format1_s {
//   Network Interface Type, Network Interface Identifier, Network Interface Direction and optional Network
// Interface Timestamp.
  bool timestamp_included = false;
  std::string ni_type;
  std::string ni_id;        //This should be an enumerated list of available interfaces
  short ni_direction;       //This should be implemented as some kind of flag
  byte_buffer message;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

struct e2_sm_ni_action_definition_format2_s {
//   Network Interface Type, Network Interface Identifier, Network
// Interface Direction, Network Interface Message Type and optional Network Interface Timestamp
  bool timestamp_included = false;
  std::string ni_type;
  std::string ni_id;        //This should be an enumerated list of available interfaces
  short ni_direction;       //This should be implemented as some kind of flag
  std::string message_fields;       //Must define which fields of the message are being requested
  byte_buffer message;

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

// E2SM-NI-ActionDefinition ::= SEQUENCE
struct e2_sm_ni_action_definition_s {
  struct action_definition_formats_c_ {
    struct types_opts {
      enum options {
        action_definition_format1,
        action_definition_format2,
        action_definition_format3,
        // ...
        action_definition_format4,
        action_definition_format5,
        nulltype
      } value;
      typedef uint8_t number_type;

      const char* to_string() const;
      uint8_t     to_number() const;
    };
    typedef enumerated<types_opts, true, 2> types;

    // choice methods
    action_definition_formats_c_() = default;
    action_definition_formats_c_(const action_definition_formats_c_& other);
    action_definition_formats_c_& operator=(const action_definition_formats_c_& other);
    ~action_definition_formats_c_() { destroy_(); }
    void        set(types::options e = types::nulltype);
    types       type() const { return type_; }
    SRSASN_CODE pack(bit_ref& bref) const;
    SRSASN_CODE unpack(cbit_ref& bref);
    void        to_json(json_writer& j) const;
    // getters
    e2_sm_ni_action_definition_format1_s& action_definition_format1()
    {
      assert_choice_type(types::action_definition_format1, type_, "actionDefinition-formats");
      return c.get<e2_sm_ni_action_definition_format1_s>();
    }
    e2_sm_ni_action_definition_format2_s& action_definition_format2()
    {
      assert_choice_type(types::action_definition_format2, type_, "actionDefinition-formats");
      return c.get<e2_sm_ni_action_definition_format2_s>();
    }

    e2_sm_ni_action_definition_format1_s& set_action_definition_format1();
    e2_sm_ni_action_definition_format2_s& set_action_definition_format2();

  private:
    types type_;
    choice_buffer_t<e2_sm_ni_action_definition_format1_s,
                    e2_sm_ni_action_definition_format2_s>
        c;

    void destroy_();
  };

  // member variables
  bool                         ext            = false;
  int64_t                      ric_style_type = 0;
  action_definition_formats_c_ action_definition_formats;
  // ...

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

}

}
