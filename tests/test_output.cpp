#include <gtest/gtest.h>
#include <cstdio>
#include "prototypes.h"

TEST(OutputTest, OutputFormat)
{
    /* Create a temporary directory to store the output files. */
    char dirname[] = "test_output";
    mkdtemp(dirname);

    /* Open the output files for writing. */
    char ergfile[BLEN];
    char trajfile[BLEN];
    snprintf(ergfile, sizeof(ergfile), "%s/test.dat", dirname);
    snprintf(trajfile, sizeof(trajfile), "%s/test.xyzt", dirname);
    FILE* erg_file = fopen(ergfile, "w");
    FILE* traj_file = fopen(trajfile, "w");

    /* Create a mdsys_t object with some data. */
    mdsys_t sys;
    sys.nfi = 42;
    sys.natoms = 2;
    sys.temp = 300.0;
    sys.ekin = 100.0;
    sys.epot = -50.0;

    /* allocate memory for the arrays */
    sys.rx = (double*) malloc(sys.natoms*sizeof(double));
    sys.ry = (double*) malloc(sys.natoms*sizeof(double));
    sys.rz = (double*) malloc(sys.natoms*sizeof(double));

    sys.rx[0] = 1.0;
    sys.ry[0] = 2.0;
    sys.rz[0] = 3.0;
    sys.rx[1] = 4.0;
    sys.ry[1] = 5.0;
    sys.rz[1] = 6.0;

    /* Call the output function. */
    output(&sys, erg_file, traj_file);

    /* Close the output files. */
    fclose(erg_file);
    fclose(traj_file);

    /* Open the trajectory file for reading and check its contents. */
    traj_file = fopen(trajfile, "r");
    char buf[1024];

    /* Check the first line. */
    fgets(buf, sizeof(buf), traj_file);
    std::stringstream expected_output;
    expected_output << sys.natoms << "\n";
    EXPECT_EQ(std::string(buf), expected_output.str());

    /* Check the second line. */
    fgets(buf, sizeof(buf), traj_file);
    expected_output.str("");
    expected_output << " nfi=" << sys.nfi 
        << " etot=" << std::setw(20) << std::fixed << std::setprecision(8) << sys.ekin + sys.epot << "\n";
    EXPECT_EQ(std::string(buf), expected_output.str());
    
    /* Check the remaining lines. */
    for (int i = 0; i < sys.natoms; i++) {
        fgets(buf, sizeof(buf), traj_file);
        char name[1024];
        double x, y, z;
        sscanf(buf, "%s %lf %lf %lf", name, &x, &y, &z);
        EXPECT_EQ(std::string(name), "Ar");
        EXPECT_DOUBLE_EQ(x, sys.rx[i]);
        EXPECT_DOUBLE_EQ(y, sys.ry[i]);
        EXPECT_DOUBLE_EQ(z, sys.rz[i]);
    }
    fclose(traj_file);

    /* Open the energy file for reading and check its contents. */
    erg_file = fopen(ergfile, "r");
    fgets(buf, sizeof(buf), erg_file);
    expected_output.str("");
    expected_output << std::setw(8) << sys.nfi << " "
                    << std::setw(20) << std::fixed << std::setprecision(8) << sys.temp << " "
                    << std::setw(20) << std::fixed << std::setprecision(8) << sys.ekin << " "
                    << std::setw(20) << std::fixed << std::setprecision(8) << sys.epot << " "
                    << std::setw(20) << std::fixed << std::setprecision(8) << sys.ekin + sys.epot << '\n';
    EXPECT_EQ(std::string(buf), expected_output.str());
    fclose(erg_file);

    /* Clean up the temporary directory and its files. */
    remove(ergfile);
    remove(trajfile);
    rmdir(dirname);
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
}
