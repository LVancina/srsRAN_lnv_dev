add_test([=[pcap_rlc_test.write_rlc_am_pdu]=]  /home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/pcap/pcap_rlc_test [==[--gtest_filter=pcap_rlc_test.write_rlc_am_pdu]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[pcap_rlc_test.write_rlc_am_pdu]=]  PROPERTIES WORKING_DIRECTORY /home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/pcap SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  pcap_rlc_test_TESTS pcap_rlc_test.write_rlc_am_pdu)
