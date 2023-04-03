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

# To compile and run the tests
Go to the build directory, compile the test files and run it:
```bash
cd build
g++ -std=c++17 $(ls ../src/*.c | grep -v 'main.c') ../tests/*.cpp -I../include -L../include -lgtest -lgtest_main -pthread -o test.x
./test.x
```