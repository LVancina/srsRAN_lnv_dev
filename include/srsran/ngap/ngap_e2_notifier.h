/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#pragma once

#include <iostream>
#include <deque>
#include "srsran/support/async/eager_async_task.h"
#include "srsran/ngap/ngap_message.h"

using namespace srsran;

class ngap_e2_notifier //: public interface_notifier    //to be implemented later
{

public:
    ngap_e2_notifier();

    bool is_active();

    void report_message(std::deque<byte_buffer>&);
        //Launch as an asynchronous coroutine?
        //Begin moving messages from ngap_messages into out_queue until active==false

    int push_message(byte_buffer);
        //Add a msg to nagap_messages queue
private:
    bool active;
    std::deque<byte_buffer> ngap_messages;
};