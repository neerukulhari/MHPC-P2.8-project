This package contains simplified MD code with multi-threading
parallelization for simulating atoms with a Lennard-Jones potential.

The bundled makefiles are set up to compile the executable once
with OpenMP disabled and once with OpenMP enabled with each build
placing the various object files in separate directories.

The examples directory contains 3 sets of example input decks
and the reference directory the corresponding outputs.

Type: make
to compile everything and: make clean
to remove all compiled objects

# Using `cmake`
To compile using `cmake` follow the steps: 
```bash
mkdir build 
cd build
cmake ..
cmake --build
```

- `make` or `make serial` to compile everything
- `ctest` to run the tests (or `make check` to check with the examples)
- `make clean` to remove all compiled files