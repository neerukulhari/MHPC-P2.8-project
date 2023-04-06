# MHPC P2.8 project: ljdm Simulation Optimization and Parallelization
The contents of this package include an MD code for the simulation of atoms using a Lennard-Jones potential that has been optimized with multi-threading parallelization.
The tasks were divided as follows:

1. Refactoring and optimizing for single-core performance, assigned to Neeraj Kulhari; 
2. openMP parallelization, assigned to Andrea Stacchetti; 
3. MPI parallelization, assigned to Iara Ota.

# How to Use the Code

To use the code, follow the following steps.

### Clone the repository:
- Clone the repository using the command `git clone https://github.com/iaraota/MHPC-P2.8-project.git`.
- Navigate to the project folder: `cd MHPC-P2.8-project`

### Configure the Makefiles:
- Create a build folder and navigate to it: `mkdir build && cd build` 
- Run `cmake ..` to configure the project.

### Build the project:
Use one of the following commands depending on the desired build option:
1. The non-optimized serial code, which was provided by Dr. Axel Kohlmeyer. Command: `make serial`; 
2. The optimized version, created by Neeraj Kulhari. Command: `make optimized`; 
3. The openMP implementation of the optimized version, created by Andrea Stacchetti. Command: `make omp`; 
4. The MPI implementation of the optimized version, created by Iara Ota. Command: `make mpi`; 
5. The hybrid version with openMP and MPI implementation. Command `make hybrid`.
6. The google tests. Command: `make unittest`

To clean the project and remove all executables and object files, use the command `make clean`.

### Run the unit tests:
To execute the unit tests, you need to compile both the tests and one version (excluding the non-optimized serial version). For example, you can run the following commands:
```bash
make unittest
make optimized
make test
``` 
These commands will compile the necessary code for the unit tests and the optimized version, allowing you to run the tests to verify the functionality of the program.

# Directory Structure

`src`: Contains the source code for the ljdm simulation.
`include`: Contains header files for the ljdm simulation.
`examples`: Contains examples for input files for the ljdm simulation.
`reference`: Contains the reference solution for the inputs in the `example` folder.
`tests`: Contains google tests for the ljdm simulation.
`Report`: Contains the final report for the benchmark of the project.
`Obj` and `Obj-serial`: Contains the object files generated during compilation.
