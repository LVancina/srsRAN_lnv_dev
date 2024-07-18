# CMake generated Testfile for 
# Source directory: /home/lucas/thesis/dev/srsRAN_Project/tests/unittests/cu_cp
# Build directory: /home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/cu_cp
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/cu_cp/cu_cp_test[1]_include.cmake")
include("/home/lucas/thesis/dev/srsRAN_Project/build/tests/unittests/cu_cp/cu_cp_config_test[1]_include.cmake")
subdirs("cell_meas_manager")
subdirs("du_processor")
subdirs("cu_up_processor")
subdirs("ue_manager")
subdirs("up_resource_manager")
subdirs("mobility")
subdirs("metrics_handler")
set_directory_properties(PROPERTIES LABELS "cu_cp")
