
execute_process(
COMMAND git rev-parse --abbrev-ref HEAD
WORKING_DIRECTORY "/home/lucas/thesis/dev/srsRAN_Project"
OUTPUT_VARIABLE GIT_BRANCH
OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
COMMAND git log -1 --format=%h
WORKING_DIRECTORY "/home/lucas/thesis/dev/srsRAN_Project"
OUTPUT_VARIABLE GIT_COMMIT_HASH
OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Generating build information")
configure_file(
  /home/lucas/thesis/dev/srsRAN_Project/lib/support/build_info/hashes.h.in
  /home/lucas/thesis/dev/srsRAN_Project/build/hashes.h
)
