cmake_minimum_required(VERSION 3.10)

# set compiler options
set(CMAKE_C_FLAGS "-Wall -g -O3 -ffast-math -fomit-frame-pointer -DLJMD_VERSION=1.0 -D_OMP=1 -fopenmp")

# Add include directories
include_directories(../include)

# Create the library "ljmd-lib"
add_library(ljdm-lib
    ../src/constants.c
    ../src/energy.c
    ../src/force.c
    ../src/input.c
    ../src/output.c
    ../src/utilities.c
    ../src/verlet.c
)
# Create the executable "ljmd.x"
add_executable(ljmd.x ../src/main.c)

# Link the library to the math library
target_link_libraries(ljmd.x ljdm-lib m)

set_target_properties(ljmd.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)

# Compile the serial version of the code
add_custom_target(parallel DEPENDS ljmd.x)

# Add the clean target
add_custom_target(clean_parrallel COMMAND rm -f *.mod *.o ../ljmd.x)

