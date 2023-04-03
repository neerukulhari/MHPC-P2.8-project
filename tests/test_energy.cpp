// compute kinetic energy for given velocities and mass
#include "gtest/gtest.h"
#include "prototypes.h"
#include "constants.h"

TEST(EnergyTest, TwoParticleInsideCutoff)
{
    mdsys_t sys;   // mdsys_t *sys

    /* set up a two particle system */
    sys.natoms = 2;
    sys.mass = 1.0;

    /* allocate memory for the arrays */
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));

    /* set up the velocities to 0*/
    sys.vx[0] = 0.0;
	sys.vx[1] = 0.0;
	sys.vy[0] = 1.0;
	sys.vy[1] = -1.0;
	sys.vz[0] = 0.0;
	sys.vz[1] = 0.0;
  
    /* call the energy routine */
    ekin(&sys);

    double e_ekin = mvsq2e;
	double e_temp = 2 * e_ekin / (3 * kboltz);

    /* check the results */
    /* velocities updated */
    EXPECT_NEAR(sys.ekin, e_ekin, 1e-5);
    EXPECT_NEAR(sys.temp, e_temp, 1e-5);

    /* free memory */
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
}

TEST(EnergyTest, ThreeParticleInsideCutoff)
{
    mdsys_t sys;   // mdsys_t *sys

    /* set up a two particle system */
    sys.natoms = 3;
    sys.mass = 1.0;

    /* allocate memory for the arrays */
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));

    /* set up the velocities to 0*/
    sys.vx[0] = 0.0;
    sys.vx[1] = 0.0;
    sys.vx[2] = 0.0;
    sys.vy[0] = 1.0;
    sys.vy[1] = -1.0;
    sys.vy[2] = 0.0;
    sys.vz[0] = 0.0;
    sys.vz[1] = 0.0;
    sys.vz[2] = 0.0;
  
    /* call the energy routine */
    ekin(&sys);

    double e_ekin = mvsq2e;
	double e_temp = e_ekin / (3 * kboltz);

    /* check the results */
    /* velocities updated */
    EXPECT_NEAR(sys.ekin, e_ekin, 1e-5);
    EXPECT_NEAR(sys.temp, e_temp, 1e-5);

    /* free memory */
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
}

TEST(EnergyTest, TwoParticleOutsideCutoff)
{
    mdsys_t sys;   // mdsys_t *sys

    /* set up a two particle system */
    sys.natoms = 2;
    sys.mass = 1.0;

    /* allocate memory for the arrays */
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));

    /* set up the velocities to 0*/
    sys.vx[0] = 0.0;
	sys.vx[1] = 0.0;
	sys.vy[0] = 1.0;
	sys.vy[1] = -1.0;
	sys.vz[0] = 0.0;
	sys.vz[1] = 0.0;
  
    /* call the energy routine */
    ekin(&sys);

    double e_ekin = mvsq2e;
    double e_temp = 2 * e_ekin / (3 * kboltz);

    /* check the results */
    /* velocities updated */
    EXPECT_NEAR(sys.ekin, e_ekin, 1e-5);
    EXPECT_NEAR(sys.temp, e_temp, 1e-5);

    /* free memory */
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
}

TEST(EnergyTest, ThreeParticleOutsideCutoff)
{
    mdsys_t sys;   // mdsys_t *sys

    /* set up a two particle system */
    sys.natoms = 3;
    sys.mass = 1.0;

    /* allocate memory for the arrays */
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));

    /* set up the velocities to 0*/
    sys.vx[0] = 0.0;
    sys.vx[1] = 0.0;
    sys.vx[2] = 0.0;
    sys.vy[0] = 1.0;
    sys.vy[1] = -1.0;
    sys.vy[2] = 0.0;
    sys.vz[0] = 0.0;
    sys.vz[1] = 0.0;
    sys.vz[2] = 0.0;
  
    /* call the energy routine */
    ekin(&sys);

    double e_ekin = mvsq2e;
	double e_temp = e_ekin / (3 * kboltz);

    /* check the results */
    /* velocities updated */
    EXPECT_NEAR(sys.ekin, e_ekin, 1e-5);
    EXPECT_NEAR(sys.temp, e_temp, 1e-5);

    /* free memory */
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
}

