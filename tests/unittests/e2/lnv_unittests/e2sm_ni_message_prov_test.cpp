/*
* This file is was produced as part of a research project by Lucas Vancina
* lnv
*/

#include "lib/e2/e2sm/e2sm_ni/e2sm_ni_message_prov.h"
// #include "/home/lucas/thesis/srsRAN_lnv_dev/include/srsran/ngap/ngap_e2_notifier.h"
#include <gtest/gtest.h>
#include "lib/ngap/ngap_e2_notifier.h"
#include "tests/unittests/e2/common/e2_test_helpers.h"
#include "srsran/support/async/async_test_utils.h"
#include "srsran/support/test_utils.h"

using namespace srsran;

// Test Fixture
class e2sm_ni_message_prov_test : public e2_test_base {
protected:
    void SetUp() override {
        ni_msg_prov = new e2sm_ni_message_prov(supported_interfaces);
        msg1 = {'T', 'e', 's', 't'};
        tmp_msg1 = {'T', 'e', 's', 't'};
        msg2 = {'D', 'a', 't', 'a'};
        tmp_msg2 = {'D', 'a', 't', 'a'};
        notifier.push_message(std::move(tmp_msg1));
        notifier.push_message(std::move(tmp_msg2));
    }

    void TearDown() override {
        delete ni_msg_prov;
    }

    std::vector<std::string> supported_interfaces = {"NG"};
    ngap_e2_notifier notifier;
    e2sm_ni_message_prov* ni_msg_prov;
    byte_buffer msg1, msg2, tmp_msg1, tmp_msg2;
};

// // Test ngap_e2_notifier behavior
// TEST_F(e2sm_ni_message_prov_test, NgapE2NotifierPushMessage) {
//     // Arrange
//     byte_buffer msg, tmp_msg = {'H', 'e', 'l', 'l', 'o'};

//     // Act
//     int result = notifier.push_message(std::move(msg));

//     // Assert
//     EXPECT_EQ(result, 1);
//     // EXPECT_FALSE(notifier.ngap_messages.empty());
//     EXPECT_EQ(notifier.ngap_messages.front(), tmp_msg);
// }

// Test report_messages function
TEST_F(e2sm_ni_message_prov_test, ReportMessages) {
    // Act
    ni_msg_prov->report_messages(notifier);

    // Assert
    EXPECT_TRUE(notifier.is_active());
    ASSERT_EQ(ni_msg_prov->num_messages(), 1); // Only the first message is pushed per function call
    EXPECT_EQ(ni_msg_prov->front(), msg1);
}

// Test get_next_message function
TEST_F(e2sm_ni_message_prov_test, GetNextMessage) {
    // Arrange
    notifier.push_message(std::move(tmp_msg1));
    ni_msg_prov->report_messages(notifier);
    
    // Act
    byte_buffer retrieved_msg = ni_msg_prov->get_next_msg();

    // Assert
    EXPECT_EQ(retrieved_msg, msg1);
    EXPECT_TRUE(ni_msg_prov->empty());
}

// // Main function for running Google Tests
// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
