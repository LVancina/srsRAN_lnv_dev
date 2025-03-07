/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

// #include "srsran/ngap/ngap_e2_notifier.h"
#include "/home/lucas/thesis/srsRAN_lnv_dev/include/srsran/ngap/ngap_e2_notifier.h"

using namespace srsran;

ngap_e2_notifier::ngap_e2_notifier() {
    active = false;
    std::cout << "***ngap_notifier instantiated***" << std::endl;
}

bool ngap_e2_notifier::is_active() {
    return active;
}

// void ngap_notifier::report_messages(coro_context<eager_async_task<int>>& ctx, std::deque<srs_cu_cp::ngap_message>& out_queue, bool active) {
void ngap_e2_notifier::report_message(std::deque<byte_buffer>& out_queue) {
    // This needs to be launched as an asynchronous coroutine?
    // if(ngap_messages.empty()) {
    //     return 0;
    // }
    active = true;

    // while(active && !ngap_messages.empty()) {
    if (active && !ngap_messages.empty()) {
        out_queue.push_back(ngap_messages.front());
        ngap_messages.pop_front();
    }
    // return 1;
}

int ngap_e2_notifier::push_message(byte_buffer msg) {
    ngap_messages.push_back(msg);
    std::cout << "***Message added to ngap_messages***" << std::endl;
    return 1;
}