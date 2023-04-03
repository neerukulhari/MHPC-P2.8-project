cmake_minimum_required(VERSION 3.10)

# set compiler options
set(CMAKE_C_FLAGS "-Wall -g -O3 -ffast-math -fomit-frame-pointer -DLJMD_VERSION=1.0")

# include directories
include_directories(../include)
include_directories(${GTEST_INCLUDE_DIRS})

ADD_EXECUTABLE(GoogleTests 
    ../src/constants.c
    ../src/energy.c
    ../src/force.c
    ../src/input.c
    ../src/utilities.c
    ../src/verlet.c
    test_constants.cpp 
    test_energy.cpp
    test_force.cpp
    test_input.cpp
    test_utilities.cpp
    test_velverlet.cpp
    test_main.cpp
)

find_package(GTest REQUIRED)
target_link_libraries(GoogleTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})   
enable_testing()

GTEST_DISCOVER_TESTS(GoogleTests)