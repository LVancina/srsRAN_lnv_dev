# CMake generated Testfile for 
# Source directory: /home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors
# Build directory: /home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/phy/upper/channel_processors
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pdcch_processor_unittest "pdcch_processor_unittest")
set_tests_properties(pdcch_processor_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;31;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pdsch_processor_unittest "pdsch_processor_unittest")
set_tests_properties(pdsch_processor_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;35;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pdsch_processor_validator_test "pdsch_processor_validator_test")
set_tests_properties(pdsch_processor_validator_test PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;47;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pucch_processor_format1_unittest "pucch_processor_format1_unittest")
set_tests_properties(pucch_processor_format1_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;56;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pucch_processor_validator_format2_test "pucch_processor_validator_format2_test")
set_tests_properties(pucch_processor_validator_format2_test PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;67;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pucch_processor_validator_format1_test "pucch_processor_validator_format1_test")
set_tests_properties(pucch_processor_validator_format1_test PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;78;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(ssb_processor_unittest "ssb_processor_unittest")
set_tests_properties(ssb_processor_unittest PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;82;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/phy/upper/channel_processors/CMakeLists.txt;0;")
subdirs("pusch")
subdirs("uci")
set_directory_properties(PROPERTIES LABELS "phy")
