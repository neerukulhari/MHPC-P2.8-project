cmake_minimum_required(VERSION 3.10)

# Copy files from the current directory to the build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/argon_108.inp
    ${CMAKE_CURRENT_BINARY_DIR}/argon_108.inp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/argon_2916.inp
    ${CMAKE_CURRENT_BINARY_DIR}/argon_2916.inp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/argon_108.rest
    ${CMAKE_CURRENT_BINARY_DIR}/argon_108.rest COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/argon_2916.rest
    ${CMAKE_CURRENT_BINARY_DIR}/argon_2916.rest COPYONLY)

# Also copy the reference files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../reference/argon_108.dat
    ${CMAKE_CURRENT_BINARY_DIR}/../reference/argon_108.dat COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../reference/argon_2916.dat
    ${CMAKE_CURRENT_BINARY_DIR}/../reference/argon_2916.dat COPYONLY)

# add check target
add_custom_target(check
COMMAND sh ${PROJECT_SOURCE_DIR}/tests/check_argon108.sh
COMMAND sh ${PROJECT_SOURCE_DIR}/tests/check_argon2916.sh
)

# add clean target
add_custom_target(clean_ex COMMAND ${CMAKE_COMMAND} -E remove -f *.xyz *.dat
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)


# The check target was done to be compatible with the old makefile. 
# We will use the CTest framework to run the tests.
enable_testing()
add_test(NAME Argon108  COMMAND sh ${PROJECT_SOURCE_DIR}/tests/check_argon108.sh)
set_tests_properties(Argon108
        PROPERTIES PASS_REGULAR_EXPRESSION ".*The argon_108 simulation was executed without errors..*")
add_test(NAME Argon2916  COMMAND sh ${PROJECT_SOURCE_DIR}/tests/check_argon2916.sh)
set_tests_properties(Argon2916
        PROPERTIES PASS_REGULAR_EXPRESSION ".*The argon_2916 simulation was executed without errors..*")