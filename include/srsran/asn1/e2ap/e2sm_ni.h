/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

/*******************************************************************************
 *
 *                   3GPP TS ASN1 E2SM NI v15.3.0 (2025-08)
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

#define ASN1_E2SM_NI_MAXOF_INT_PROTOCOL_TESTS 15
#define ASN1_E2SM_NI_MAXOF_RAN_UE_GROUPS      255
#define ASN1_E2SM_NI_MAXOF_ACTION_PARAMETERS  255
#define ASN1_E2SM_NI_MAXOF_RAN_PARAMETERS     65535
#define ASN1_E2SM_NI_MAXOF_NI_TYPES           63
#define ASN1_E2SM_NI_MAXOF_RIC_STYLES         63

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/
const uint32_t None = 2147483647;

// GlaboENB-ID ::= SEQUENCE
struct global_enb_id_s {
  bool ext = false;
  std::string plmn_id;
  std::string enb_id;
    // ...

  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

//ENB-ID ::= CHOICE
struct enb_id_c {
  struct types_opts{
    enum options{ macro_enb_id, home_enb_id, /*...*/ short_macro_enb_id, 
      long_macro_enb_id, nulltype};
    // ***These options will be defined later***
  };
  typedef enumerated<types_opts, true> types;

  // Choice methods
  enb_id_c() = default;

  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;

private:
  types                   type_;
  choice_buffer_t<real_s> c;

  void destroy_();
};

// GlobalenGNB-ID ::= SEQUENCE
struct global_gnb_id_s {
  bool ext = false;
  std::string plmn_id;
  std::string gnb_id;
  //...
  
  // sequence methods
  SRSASN_CODE pack(bit_ref& bref) const;
  SRSASN_CODE unpack(cbit_ref& bref);
  void        to_json(json_writer& j) const;
};

// TODO - validate AI generated code below
//ENGNB-ID ::= CHOICE
struct engnb_id_c {
  struct types_opts {
    enum options{
      gnb_id
    };
    const char* to_string() const;
  };

  // Track which option is active
  types_opts::options type;

  // Represent BIT STRING as a vector<uint8_t> plus explicit length
  struct BitString {
      std::vector<uint8_t> bits;  // Raw bytes
      uint8_t num_bits;           // Actual bit length (22–32)

      BitString() : num_bits(0) {}
      BitString(const std::vector<uint8_t>& data, uint8_t len) 
          : bits(data), num_bits(len) {
          if (len < 22 || len > 32) {
            // TODO - Figure out another way to handle errors
              // throw std::runtime_error("ENGNB-ID: gNB-ID must be 22..32 bits");
          }
      }

      std::string to_hex() const {
          std::string out;
          for (uint8_t b : bits) {
              char buf[3];
              snprintf(buf, sizeof(buf), "%02X", b);
              out += buf;
          }
          return out;
      }
  };

  BitString gnb_id;

  static engnb_id_c make_gnb_id(const std::vector<uint8_t>& data, uint8_t len) {
      engnb_id_c id;
      id.type = types_opts::gnb_id;
      id.gnb_id = BitString(data, len);
      return id;
  };
};
// END AI Code

// GlobalNG-RANNode-ID ::= CHOICE
struct globalng_rannode_id_c {
  struct types_opts {
    enum options {
      gnb,
      ng_enb
      /*...*/
    };
    const char* to_string() const;
  };
};



//######################## AI GENERATED STUFF #################################

// E2SM-KPM-ActionDefinition-Format1 ::= SEQUENCE
// Format1 is for full messages.
struct e2_sm_ni_action_definition_format1_s {
//   Network Interface Type, Network Interface Identifier, Network Interface Direction and optional Network
// Interface Timestamp.
  bool timestamp_included = false;
  std::string ni_type;
  std::string ni_id;        //This should be an enumerated list of available interfaces

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

} //END namespace e2sm_ni

} //END namespace asn1
/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

/*******************************************************************************
 *
 *                   3GPP TS ASN1 E2SM NI v15.3.0 (2025-08)
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

#define ASN1_E2SM_NI_MAXOF_INT_PROTOCOL_TESTS 15
#define ASN1_E2SM_NI_MAXOF_RAN_UE_GROUPS      255
#define ASN1_E2SM_NI_MAXOF_ACTION_PARAMETERS  255
#define ASN1_E2SM_NI_MAXOF_RAN_PARAMETERS     65535
#define ASN1_E2SM_NI_MAXOF_NI_TYPES           63
#define ASN1_E2SM_NI_MAXOF_RIC_STYLES         63

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/
const uint32_t None = 2147483647;

// GlaboENB-ID ::= SEQUENCE
struct global_enb_id_s {
