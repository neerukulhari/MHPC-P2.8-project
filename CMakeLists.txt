cmake_minimum_required(VERSION 3.10)
project(ljmd VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_FLAGS "-Wall -g -O3 -ffast-math -fomit-frame-pointer -DLJMD_VERSION=1.0")
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b5fd99bbd55ebe1a3488b8ea3717fba089293457.zip 
  # The link above gets the latest version of googletest made on Mar 30, 2023
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add the project folders where the other CMakeLists.txt files are located
add_subdirectory(examples)
add_subdirectory(Obj)
add_subdirectory(tests)
# Obj-serial is kept for reference to the original serial code
add_subdirectory(Obj-serial)

# define target for cleaning
add_custom_target(clean_all
    COMMAND ${CMAKE_MAKE_PROGRAM} -C Obj-serial clean_parallel
    COMMAND ${CMAKE_MAKE_PROGRAM} -C examples clean_serial
    COMMAND ${CMAKE_MAKE_PROGRAM} -C examples clean_ex
)

# define target for checking
add_custom_target(check_all
    DEPENDS ljmd-serial
    COMMAND ${CMAKE_MAKE_PROGRAM} -C examples check
)

# Add tests defined in example and test folders
enable_testing()