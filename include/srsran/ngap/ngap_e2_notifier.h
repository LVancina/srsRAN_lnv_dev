/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#pragma once

#include "srsran/ngap/ngap_message.h"
#include <deque>

using namespace srsran;
// using namespace srs_cu_cp;

class ngap_e2_notifier //: public interface_notifier    To-Do: Implement parent class later
{
public:
    ngap_e2_notifier();

    short report_messages(std::deque<byte_buffer>& out_queue);

    int push_message(byte_buffer msg);

    bool is_active() const;

    bool empty() const;
    
    byte_buffer get_next_message();

private:
    std::deque<byte_buffer> ngap_messages;
    bool active;
};
