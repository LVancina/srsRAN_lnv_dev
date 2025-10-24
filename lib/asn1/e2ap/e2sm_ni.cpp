/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#include "srsran/asn1/e2ap/e2sm_ni.h"

using namespace asn1;
using namespace asn1::e2sm_ni;

/*******************************************************************************
 *                                Struct Methods
 ******************************************************************************/

SRSASN_CODE plmn_identity_s::pack(bit_ref& bref) const {
    for (uint8_t b : value) {
        if (!bref.pack(b,8)) {
            return asn1::SRSASN_ERROR_ENCODE_FAIL;
        }
    }
    return asn1::SRSASN_SUCCESS;
}

asn1::SRSASN_CODE plmn_identity_s::unpack (cbit_ref& bref) {
  for (size_t i = 0; i < 3; i++) {
    if (!bref.unpack(value[i],8)) {
      return asn1::SRSASN_ERROR_DECODE_FAIL;
    }
  }
  return asn1::SRSASN_SUCCESS;
}

void plmn_identity_s::to_json(asn1::json_writer& j) const {
  std::string hex;
  for (auto b : value) {
    char buf[3];
    snprintf(buf, sizeof(buf), "%02X", b);
    hex += buf;
  }
  j.write_str("PLMN-Identity", hex.c_str());
}
