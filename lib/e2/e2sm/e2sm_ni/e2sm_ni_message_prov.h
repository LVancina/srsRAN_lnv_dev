/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#pragma once

#include <vector>
#include <string>
#include <deque>
#include "srsran/ngap/ngap_message.h"
#include "srsran/ngap/ngap_e2_notifier.h"

using namespace srsran;

class e2sm_ni_message_prov
{
public:
    e2sm_ni_message_prov(std::vector<std::string>);

    void report_messages(ngap_e2_notifier&);

    byte_buffer get_next_message();

    int num_messages();

    byte_buffer front();

    bool empty();

    /// Helper functions to check if an interface is supported, etc...
private:
    std::vector<std::string> supported_interfaces;
    std::deque<byte_buffer> if_messages;
};