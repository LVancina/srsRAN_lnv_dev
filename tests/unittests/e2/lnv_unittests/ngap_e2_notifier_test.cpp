/*
* Test file for ngap_e2_notifier class.
* Written by Lucas Vancina for research purposes with assistance from ChatGPT.
*/

#include <gtest/gtest.h>
#include <vector>
#include "srsran/ngap/ngap_e2_notifier.h"
#include "tests/unittests/e2/common/e2_test_helpers.h"
#include "srsran/support/async/async_test_utils.h"
#include "srsran/support/test_utils.h"

using namespace srsran;

class ngap_e2_notifier_test : public e2_test_base
{
    protected:
        // Fixture setup; runs before each test
        void SetUp() override {
            notifier = new ngap_e2_notifier();
        }

        void TearDown() override {
            delete notifier;
        }

        ngap_e2_notifier* notifier;
};

TEST_F(ngap_e2_notifier_test, PushAndReportMessage) {
    // ngap_e2_notifier notifier;

    // Initialize byte_buffer with proper data
    std::vector<uint8_t> data = {0x01, 0x02, 0x03};
    byte_buffer msg(data.begin(), data.end());

    // Push the message to the notifier
    ASSERT_EQ(notifier->push_message(std::move(msg)), 1);
    // ASSERT_EQ(notifier->push_message(msg), 1);

    // Prepare an output queue
    std::deque<byte_buffer> out_queue;

    // Report the message from the notifier
    notifier->report_message(out_queue);

    // Verify the message was moved to the out_queue
    ASSERT_EQ(out_queue.size(), 2);
    EXPECT_EQ(out_queue.front(), msg);
}
