/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#include "e2sm_ni_message_prov.h"
// #include "../../e2sm/e2sm_ni/e2sm_ni_message_prov.h"
#include <iostream>

using namespace srsran;

//Constructor
e2sm_ni_message_prov::e2sm_ni_message_prov(
    std::vector<std::string> supported_interfaces_) : supported_interfaces(supported_interfaces_) {
        this->if_messages = std::deque<byte_buffer>{};
        std::cout << "message provider instantiated" << std::endl;
        // Additional checks
     }

short e2sm_ni_message_prov::report_messages(ngap_e2_notifier& notifier) {
    short num_messages;
    num_messages = notifier.report_messages(if_messages);
    return num_messages;
}

byte_buffer e2sm_ni_message_prov::get_next_msg() {
    byte_buffer next = std::move(if_messages.front());
    if_messages.pop_front();
    return next;
}

bool e2sm_ni_message_prov::empty() {
    return if_messages.empty();
}

int e2sm_ni_message_prov::num_messages() {
    return if_messages.size();
}

byte_buffer e2sm_ni_message_prov::front() {
    byte_buffer front = std::move(if_messages.front());
    return front;
}
