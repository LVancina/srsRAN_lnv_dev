# CMake generated Testfile for 
# Source directory: /home/lucas/thesis/dev/srsRAN_Project/tests/unittests/asn1
# Build directory: /home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/asn1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/asn1/asn1_rrc_nr_test[1]_include.cmake")
include("/home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/asn1/asn1_e1ap_test[1]_include.cmake")
include("/home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/asn1/asn1_e2ap_test[1]_include.cmake")
include("/home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/asn1/asn1_f1ap_test[1]_include.cmake")
include("/home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/asn1/asn1_ngap_test[1]_include.cmake")
add_test(asn1_utils_test "asn1_utils_test")
set_tests_properties(asn1_utils_test PROPERTIES  _BACKTRACE_TRIPLES "/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/asn1/CMakeLists.txt;25;add_test;/home/lucas/thesis/dev/srsRAN_Project/tests/unittests/asn1/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "asn1")
