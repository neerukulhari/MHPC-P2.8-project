cmake_minimum_required(VERSION 3.10)
project(ljmd VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_FLAGS "-Wall -g -O3 -ffast-math -fomit-frame-pointer -DLJMD_VERSION=1.0")

# adding subdirectories
add_subdirectory(examples)
#including thr include directories with the header files
include_directories(include)

add_executable(ljmd-serial.x src/main.c 
    src/constants.c
    src/energy.c
    src/force.c
    src/input.c
    src/output.c
    src/utilities.c
    src/verlet.c
    include/constants.h
    include/prototypes.h
    include/structures.h
    include/utilities.h)

# add libraries to link to the .exe
add_library(constants src/constants.c include/constants.h)
add_library(energy src/energy.c )
add_library(force src/force.c )
add_library(input src/input.c )
add_library(output src/output.c )
add_library(utilities src/utilities.c include/utilities.h)
add_library(verlet src/verlet.c)

#target include directories and link libraries

target_include_directories(ljmd-serial.x PUBLIC ${CMAKE_BINARY_DIR})
target_link_libraries(ljmd-serial.x PRIVATE ${SOURCE_FILES} )


# define target for make serial
add_custom_target(serial
    COMMAND make
)

# define target for make parallel
add_custom_target(parallel
    COMMAND make 
)


# define target for cleaning
add_custom_target(clean-files COMMAND rm -f *.mod *.o *.x)

# define target for running checks
add_custom_target(run-checks
    DEPENDS ljmd-serial.x
    COMMAND ${CMAKE_MAKE_PROGRAM} -C examples check
)


# The check target was done to be compatible with the old makefile. 
# We will use the CTest framework to run the tests.
enable_testing()

add_test(NAME Argon108  COMMAND sh ${PROJECT_SOURCE_DIR}/tests/check_argon108.sh)
set_tests_properties(Argon108
        PROPERTIES PASS_REGULAR_EXPRESSION ".*The argon_108 simulation was executed without errors..*")
add_test(NAME Argon2916  COMMAND sh ${PROJECT_SOURCE_DIR}/tests/check_argon2916.sh)
set_tests_properties(Argon2916
        PROPERTIES PASS_REGULAR_EXPRESSION ".*The argon_2916 simulation was executed without errors..*")