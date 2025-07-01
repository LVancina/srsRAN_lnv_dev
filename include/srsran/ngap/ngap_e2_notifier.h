/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#pragma once

#include "srsran/ngap/ngap_message.h"
#include <deque>

using namespace srsran;
using namespace srs_cu_cp;

class ngap_e2_notifier //: public interface_notifier    To-Do: Implement parent class later
{
    std::deque<ngap_message> ngap_messages;

    int report_messages(std::deque<ngap_message>& out_queue, bool active=true);

    int push_message(ngap_message msg);
};