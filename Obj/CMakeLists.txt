cmake_minimum_required(VERSION 3.10)

# set compiler options
set(CMAKE_C_FLAGS "-Wall -g -O3 -ffast-math -fomit-frame-pointer -DLJMD_VERSION=1.0")

# Add include directories
include_directories(../include)

# Add MPI support
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

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
# Create the mpi executable "ljmd_mpi.x"
add_executable(ljmd_mpi.x ../src/main.c)
# Create the openmp executable "ljmd_omp.x"
add_executable(ljmd_omp.x ../src/main.c)
# Create the hybrid executable "ljmd_hybrid.x"
add_executable(ljmd_hybrid.x ../src/main.c)

# Link the library to the math library
target_link_libraries(ljmd.x ljdm-lib m)
target_link_libraries(ljmd_mpi.x ljdm-lib m ${MPI_LIBRARIES})
target_link_libraries(ljmd_omp.x ljdm-lib m)
target_link_libraries(ljmd_hybrid.x ljdm-lib m ${MPI_LIBRARIES})

# Compile the serial optimized version of the code
set_target_properties(ljmd.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)
# Compile the serial optimized version of the code
add_custom_target(optimized DEPENDS ljmd.x)

# Add MPI flags
set_target_properties(ljmd_mpi.x PROPERTIES COMPILE_FLAGS "-D_MPI=1" RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)
# Create the mpi target
add_custom_target(mpi DEPENDS ljmd_mpi.x)
# Rename executable
set_target_properties(ljmd_mpi.x PROPERTIES OUTPUT_NAME ljmd.x)

# Add OpenMP flags
set_target_properties(ljmd_omp.x PROPERTIES COMPILE_FLAGS "-fopenmp -D_OPENMP=1" LINK_FLAGS "-fopenmp" RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)
# Create the openmp target
add_custom_target(omp DEPENDS ljmd_omp.x)
# Rename executable
set_target_properties(ljmd_omp.x PROPERTIES OUTPUT_NAME ljmd.x)

# Add MPI and OpenMP flags
set_target_properties(ljmd_hybrid.x PROPERTIES COMPILE_FLAGS "-fopenmp -D_OPENMP=1 -D_MPI=1" LINK_FLAGS "-fopenmp" RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)
# Create the hybrid target
add_custom_target(hybrid DEPENDS ljmd_hybrid.x)
# Rename executable
set_target_properties(ljmd_hybrid.x PROPERTIES OUTPUT_NAME ljmd.x)


# Add the clean target
add_custom_target(clean_parrallel COMMAND rm -f *.mod *.o ../ljmd.x)

