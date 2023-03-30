cmake_minimum_required(VERSION 3.10)
project(ljmd VERSION 1.0 LANGUAGES C)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-Wall -g -O3 -ffast-math -fomit-frame-pointer -DLJMD_VERSION=1.0")

# Add the project folders where the other CMakeLists.txt files are located
add_subdirectory(Obj-serial)
add_subdirectory(examples)

# define target for make serial
add_custom_target(serial
    COMMAND make
)

# define target for cleaning
add_custom_target(clean_all
    COMMAND ${CMAKE_MAKE_PROGRAM} -C Obj-serial clean_obj
    COMMAND ${CMAKE_MAKE_PROGRAM} -C examples clean_ex
)

# define target for checking
add_custom_target(check_all
    DEPENDS ljmd-serial
    COMMAND ${CMAKE_MAKE_PROGRAM} -C examples check
)
