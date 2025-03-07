/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#include "e2sm_ni_message_prov.h"

using namespace srsran;

e2sm_ni_message_prov::e2sm_ni_message_prov(std::vector<std::string> supported_interfaces_) {
    supported_interfaces = supported_interfaces_;
}

void e2sm_ni_message_prov::report_messages(ngap_e2_notifier& notifier) {
    /// TODO - There can be more than one notifier. How can I handle multiple updating at the same time.
    notifier.report_message(if_messages);
    /// TODO - mutual exclusion needed for shared queue.
}

byte_buffer e2sm_ni_message_prov::get_next_message() {
    byte_buffer next = std::move(if_messages.front());
    if_messages.pop_front();
    return next;
}

/// Helper functions as needed...