To compile without a make file do the following:

```bash
mkdir build
cd build
gcc ../src/*.c -I ../include -L ../include -o ljmd-serial.x -DLJMD_VERSION=1.0 -lm
```

Then to test if it runs correctly go to the examples folder and run the tests:
```bash
cd ../../examples
sh ../LJMD_serial/tests/check_argon108.sh
sh ../LJMD_serial/tests/check_argon2916.sh
```

The result should print **"The argon_# simulation was executed without errors."**