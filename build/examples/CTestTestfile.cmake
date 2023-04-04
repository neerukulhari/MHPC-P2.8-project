# CMake generated Testfile for 
# Source directory: /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/examples
# Build directory: /home/neeraj/Desktop/MHPC/MHPC-P2.8-project/build/examples
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Argon108 "sh" "/home/neeraj/Desktop/MHPC/MHPC-P2.8-project/tests/check_argon.sh" "../ljmd.x" "argon_108")
set_tests_properties(Argon108 PROPERTIES  PASS_REGULAR_EXPRESSION ".*The argon_108 simulation was executed without errors..*" _BACKTRACE_TRIPLES "/home/neeraj/Desktop/MHPC/MHPC-P2.8-project/examples/CMakeLists.txt;34;add_test;/home/neeraj/Desktop/MHPC/MHPC-P2.8-project/examples/CMakeLists.txt;0;")
add_test(Argon2916 "sh" "/home/neeraj/Desktop/MHPC/MHPC-P2.8-project/tests/check_argon.sh" "../ljmd.x" "argon_2916")
set_tests_properties(Argon2916 PROPERTIES  PASS_REGULAR_EXPRESSION ".*The argon_2916 simulation was executed without errors..*" _BACKTRACE_TRIPLES "/home/neeraj/Desktop/MHPC/MHPC-P2.8-project/examples/CMakeLists.txt;39;add_test;/home/neeraj/Desktop/MHPC/MHPC-P2.8-project/examples/CMakeLists.txt;0;")
