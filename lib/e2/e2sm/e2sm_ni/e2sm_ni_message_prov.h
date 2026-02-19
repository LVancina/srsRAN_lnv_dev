/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#pragma once

// #include "e2sm/e2sm_kpm/e2sm_kpm_metric_defs.h"
// #include "e2sm_kpm_metric_defs.h"
// #include "../e2sm_kpm/e2sm_kpm_utils.h"
// #include "../include/srsran/ngap/ngap_e2_notifier.h"
#include "../../../ngap/ngap_e2_notifier.h"
// #include "ngap_e2_notifier.h"
// #include "srsran/adt/optional.h"
// #include "srsran/asn1/asn1_utils.h"
// #include "srsran/asn1/e2ap/e2sm_kpm.h"
// #include "srsran/e2/e2.h"
// #include "srsran/e2/e2sm/e2sm.h"
// #include "srsran/e2/e2sm/e2sm_kpm.h"
// #include "srsran/f1ap/du/f1ap_du.h"
// #include <map>
// #include <numeric>
#include <deque>

using namespace srsran;

class e2sm_ni_message_prov
{
public:
    e2sm_ni_message_prov(std::vector<std::string> supported_interfaces_);
    short report_messages(ngap_e2_notifier& notifier); //TODO - abstract the notifier class with polymorphism
    byte_buffer get_next_msg();

    bool empty();

    int num_messages();

    byte_buffer front();

    byte_buffer back();

private:
    std::vector<std::string> supported_interfaces;
    std::deque<byte_buffer> if_messages;
};
