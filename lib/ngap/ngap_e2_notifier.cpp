/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#include "ngap_e2_notifier.h"
// #include "srsran/ngap/ngap_e2_notifier.h"


using namespace srsran;
// using namespace srs_cu_cp;

// Constructor
ngap_e2_notifier::ngap_e2_notifier() {
    this->active = false;
    std::cout << "ngap_notifier initialized." << std::endl;
}

// Report messages function
short ngap_e2_notifier::report_messages(std::deque<byte_buffer>& out_queue) {
    short num_messages = 0;
    this->active = true;
    // Check if the ngap_messages deque is empty
    if (ngap_messages.empty()) {
        std::cout << "No messages to report." << std::endl;
        return 0; // No messages to report
    }

    // Begin moving messages from ngap_messages into out_queue until active is false
    while (active && !ngap_messages.empty()) {
        // Move the front message from ngap_messages to out_queue
        std::cout << "reporting message" << std::endl;
        out_queue.push_back(ngap_messages.front());
        ngap_messages.pop_front();
        num_messages += 1;
    }

    std::cout << "Report messages complete" << std::endl;
    return num_messages; // Return the number of messages reported
}

// Push message function
int ngap_e2_notifier::push_message(byte_buffer msg) {
    // Add the msg to ngap_messages queue
    ngap_messages.push_back(std::move(msg));
    std::cout << "Message pushed to ngap_messages queue." << std::endl;
    return 1; // Return 1 to indicate the message was successfully added
}

byte_buffer ngap_e2_notifier::get_next_message() {  
    std::cout << "Entered get_next_message" << std::endl;
    byte_buffer empty_buf = {};
    if (ngap_messages.empty()) {
        return empty_buf;
    }
    byte_buffer nxt_msg = std::move(this->ngap_messages.front());
    this->ngap_messages.pop_front();
    std::cout << "Exiting get_next_message" << std::endl;
    return nxt_msg;
}

bool ngap_e2_notifier::is_active() const {
    return this->active;
}

bool ngap_e2_notifier::empty() const {
    return this->ngap_messages.empty();
}
