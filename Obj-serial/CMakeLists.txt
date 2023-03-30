cmake_minimum_required(VERSION 3.10)

# set compiler options
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-Wall -g -O3 -ffast-math -fomit-frame-pointer -DLJMD_VERSION=1.0")

# Create the object file "ljmd.o" from the source file "../src/ljmd.c"
add_library(ljmd.o OBJECT ../src/ljmd.c)
# Link the library to the math library
target_link_libraries(ljmd.o PRIVATE m)

# Add executable "ljmd-serial.x" from the object file "ljmd.o"
add_executable(ljmd-serial.x $<TARGET_OBJECTS:ljmd.o>)
# Set output directory to parent folder
set_target_properties(ljmd-serial.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)

# Add the clean target
add_custom_target(clean_obj COMMAND rm -f *.mod *.o ../ljmd-serial.x)

