#include "gtest/gtest.h"
#include "prototypes.h"
#include "structures.h"


TEST(ForceTest, TwoParticleInsideCutoff) {
    mdsys_t sys;

    /* set up a two particle system */
    sys.natoms = 2;
    sys.rcut = 3.0;
    sys.box = 10.0;
    sys.epsilon = 1.0;
    sys.sigma = 1.0;

    /* allocate memory for the arrays */
    sys.rx = (double*) malloc(sys.natoms*sizeof(double));
    sys.ry = (double*) malloc(sys.natoms*sizeof(double));
    sys.rz = (double*) malloc(sys.natoms*sizeof(double));
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));
    sys.fx = (double*) malloc(sys.natoms*sizeof(double));
    sys.fy = (double*) malloc(sys.natoms*sizeof(double));
    sys.fz = (double*) malloc(sys.natoms*sizeof(double));

    /* set up the positions, always small enough to be inside the cutoff */
    sys.rx[0] = 1.0;
    sys.ry[0] = 1.0;
    sys.rz[0] = 1.0;
    sys.rx[1] = 1.5;
    sys.ry[1] = 1.5;
    sys.rz[1] = 1.5;
    
    /* call the force routine */
    force(&sys);
    
    /* check the results */
    EXPECT_NEAR(sys.epot, 12.99314, 1e-5);
    EXPECT_NEAR(sys.fx[0], -141.87105, 1e-5);
    EXPECT_NEAR(sys.fy[0], -141.87105, 1e-5);
    EXPECT_NEAR(sys.fz[0], -141.87105, 1e-5);
    EXPECT_NEAR(sys.fx[1], 141.87105, 1e-5);
    EXPECT_NEAR(sys.fy[1], 141.87105, 1e-5);
    EXPECT_NEAR(sys.fz[1], 141.87105, 1e-5);
    
    /* free the memory */
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
}

TEST(ForceTest, ThreeParticleInsideCutoff) {
    mdsys_t sys;
    /* set up a three particle system */
    sys.natoms = 3;
    sys.rcut = 3.0;
    sys.box = 10.0;
    sys.epsilon = 1.0;
    sys.sigma = 1.0;

    /* allocate memory for the arrays */
    sys.rx = (double*) malloc(sys.natoms*sizeof(double));
    sys.ry = (double*) malloc(sys.natoms*sizeof(double));
    sys.rz = (double*) malloc(sys.natoms*sizeof(double));
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));
    sys.fx = (double*) malloc(sys.natoms*sizeof(double));
    sys.fy = (double*) malloc(sys.natoms*sizeof(double));
    sys.fz = (double*) malloc(sys.natoms*sizeof(double));

    /* set up the positions, always small enough to be inside the cutoff */
    sys.rx[0] = 1.0;
    sys.ry[0] = 1.0;
    sys.rz[0] = 1.0;
    sys.rx[1] = 1.5;
    sys.ry[1] = 1.5;
    sys.rz[1] = 1.5;
    sys.rx[2] = 2.0;
    sys.ry[2] = 2.0;
    sys.rz[2] = 2.0;
    
    /* call the force routine */
    force(&sys);
    
    /* check the results */
    EXPECT_NEAR(sys.epot, 25.84362, 1e-5);
    EXPECT_NEAR(sys.fx[0], -141.59671, 1e-5);
    EXPECT_NEAR(sys.fy[0], -141.59671, 1e-5);
    EXPECT_NEAR(sys.fz[0], -141.59671, 1e-5);
    EXPECT_NEAR(sys.fx[1], 0.0, 1e-5);
    EXPECT_NEAR(sys.fy[1], 0.0, 1e-5);
    EXPECT_NEAR(sys.fz[1], 0.0, 1e-5);
    EXPECT_NEAR(sys.fx[2], 141.59671, 1e-5);
    EXPECT_NEAR(sys.fy[2], 141.59671, 1e-5);
    EXPECT_NEAR(sys.fz[2], 141.59671, 1e-5);
    
    /* free the memory */
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
}

TEST(ForceTest, TwoParticleOutsideCutoff) {
    mdsys_t sys;

    /* set up a two particle system */
    sys.natoms = 2;
    sys.rcut = 3.0;
    sys.box = 10.0;
    sys.epsilon = 1.0;
    sys.sigma = 1.0;

    /* allocate memory for the arrays */
    sys.rx = (double*) malloc(sys.natoms*sizeof(double));
    sys.ry = (double*) malloc(sys.natoms*sizeof(double));
    sys.rz = (double*) malloc(sys.natoms*sizeof(double));
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));
    sys.fx = (double*) malloc(sys.natoms*sizeof(double));
    sys.fy = (double*) malloc(sys.natoms*sizeof(double));
    sys.fz = (double*) malloc(sys.natoms*sizeof(double));

    /* set up the positions, at least one large enough to be inside the cutoff */
    sys.rx[0] = 1.0;
    sys.ry[0] = 1.0;
    sys.rz[0] = 1.0;
    sys.rx[1] = 1.5;
    sys.ry[1] = 1.5;
    sys.rz[1] = 3.5;
    
    /* call the force routine */
    force(&sys);
    
    /* check the results */
    EXPECT_NEAR(sys.epot, -0.01296, 1e-5);
    EXPECT_NEAR(sys.fx[0], 0.00574, 1e-5);
    EXPECT_NEAR(sys.fy[0], 0.00574, 1e-5);
    EXPECT_NEAR(sys.fz[0], 0.02871, 1e-5);
    EXPECT_NEAR(sys.fx[1], -0.00574, 1e-5);
    EXPECT_NEAR(sys.fy[1], -0.00574, 1e-5);
    EXPECT_NEAR(sys.fz[1], -0.02871, 1e-5);
    
    /* free the memory */
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
}

TEST(ForceTest, ThreeParticleOutsideCutoff) {
    mdsys_t sys;
    /* set up a three particle system */
    sys.natoms = 3;
    sys.rcut = 3.0;
    sys.box = 10.0;
    sys.epsilon = 1.0;
    sys.sigma = 1.0;

    /* allocate memory for the arrays */
    sys.rx = (double*) malloc(sys.natoms*sizeof(double));
    sys.ry = (double*) malloc(sys.natoms*sizeof(double));
    sys.rz = (double*) malloc(sys.natoms*sizeof(double));
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));
    sys.fx = (double*) malloc(sys.natoms*sizeof(double));
    sys.fy = (double*) malloc(sys.natoms*sizeof(double));
    sys.fz = (double*) malloc(sys.natoms*sizeof(double));

    /* set up the positions, at least one large enough to be inside the cutoff */
    sys.rx[0] = 1.0;
    sys.ry[0] = 1.0;
    sys.rz[0] = 1.0;
    sys.rx[1] = 1.5;
    sys.ry[1] = 1.5;
    sys.rz[1] = 4.5;
    sys.rx[2] = 2.0;
    sys.ry[2] = 2.0;
    sys.rz[2] = 4.0;
    
    /* call the force routine */
    force(&sys);
    
    /* check the results */
    EXPECT_NEAR(sys.epot, 12.99314, 1e-5);
    EXPECT_NEAR(sys.fx[0], 0.0, 1e-5);
    EXPECT_NEAR(sys.fy[0], 0.0, 1e-5);
    EXPECT_NEAR(sys.fz[0], 0.0, 1e-5);
    EXPECT_NEAR(sys.fx[1], -141.87106, 1e-5);
    EXPECT_NEAR(sys.fy[1], -141.87106, 1e-5);
    EXPECT_NEAR(sys.fz[1], 141.87106, 1e-5);
    EXPECT_NEAR(sys.fx[2], 141.87106, 1e-5);
    EXPECT_NEAR(sys.fy[2], 141.87106, 1e-5);
    EXPECT_NEAR(sys.fz[2], -141.87106, 1e-5);
    
    /* free the memory */
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
}

TEST(VelVerletTest, TwoParticleInsideCutoff) {
    mdsys_t sys;

    /* set up a two particle system */
    sys.natoms = 2;
    sys.rcut = 3.0;
    sys.box = 10.0;
    sys.epsilon = 1.0;
    sys.sigma = 1.0;

    sys.dt = 0.1;
    sys.mass = 0.1;

    /* allocate memory for the arrays */
    sys.rx = (double*) malloc(sys.natoms*sizeof(double));
    sys.ry = (double*) malloc(sys.natoms*sizeof(double));
    sys.rz = (double*) malloc(sys.natoms*sizeof(double));
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));
    sys.fx = (double*) malloc(sys.natoms*sizeof(double));
    sys.fy = (double*) malloc(sys.natoms*sizeof(double));
    sys.fz = (double*) malloc(sys.natoms*sizeof(double));

    /* set up the positions, always small enough to be inside the cutoff */
    sys.rx[0] = 1.0;
    sys.ry[0] = 1.0;
    sys.rz[0] = 1.0;
    sys.rx[1] = 1.5;
    sys.ry[1] = 1.5;
    sys.rz[1] = 1.5;
    
    /* set up the velocities to 0*/
    sys.vx[0] = 0.0;
    sys.vy[0] = 0.0;
    sys.vz[0] = 0.0;
    sys.vx[1] = 0.0;
    sys.vy[1] = 0.0;
    sys.vz[1] = 0.0;

    /* set up the forces */
    sys.fx[0] = 100.0;
    sys.fy[0] = 100.0;
    sys.fz[0] = 100.0;
    sys.fx[1] = 50.0;
    sys.fy[1] = 50.0;
    sys.fz[1] = 50.0;
    
    /* call the force routine */
    velverlet(&sys);
    
    /* check the results */
    /* positions updated */
    EXPECT_NEAR(sys.rx[0], 1.00209, 1e-5);
    EXPECT_NEAR(sys.ry[0], 1.00209, 1e-5);
    EXPECT_NEAR(sys.rz[0], 1.00209, 1e-5);
    EXPECT_NEAR(sys.rx[1], 1.50104, 1e-5);
    EXPECT_NEAR(sys.ry[1], 1.50104, 1e-5);
    EXPECT_NEAR(sys.rz[1], 1.50104, 1e-5);

    /* velocities updated */
    EXPECT_NEAR(sys.vx[0], -0.00968, 1e-5);
    EXPECT_NEAR(sys.vy[0], -0.00968, 1e-5);
    EXPECT_NEAR(sys.vz[0], -0.00968, 1e-5);
    EXPECT_NEAR(sys.vx[1], 0.04106, 1e-5);
    EXPECT_NEAR(sys.vy[1], 0.04106, 1e-5);
    EXPECT_NEAR(sys.vz[1], 0.04106, 1e-5);

    /* forces updated */
    EXPECT_NEAR(sys.fx[0], -146.27311, 1e-5);
    EXPECT_NEAR(sys.fy[0], -146.27311, 1e-5);
    EXPECT_NEAR(sys.fz[0], -146.27311, 1e-5);
    EXPECT_NEAR(sys.fx[1], 146.27311, 1e-5);
    EXPECT_NEAR(sys.fy[1], 146.27311, 1e-5);
    EXPECT_NEAR(sys.fz[1], 146.27311, 1e-5);

    /* free the memory */
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
}

TEST(VelVerletTest, ThreeParticleInsideCutoff) {
    mdsys_t sys;

    /* set up a two particle system */
    sys.natoms = 3;
    sys.rcut = 3.0;
    sys.box = 10.0;
    sys.epsilon = 1.0;
    sys.sigma = 1.0;

    sys.dt = 0.1;
    sys.mass = 0.1;

    /* allocate memory for the arrays */
    sys.rx = (double*) malloc(sys.natoms*sizeof(double));
    sys.ry = (double*) malloc(sys.natoms*sizeof(double));
    sys.rz = (double*) malloc(sys.natoms*sizeof(double));
    sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));
    sys.fx = (double*) malloc(sys.natoms*sizeof(double));
    sys.fy = (double*) malloc(sys.natoms*sizeof(double));
    sys.fz = (double*) malloc(sys.natoms*sizeof(double));

    /* set up the positions, always small enough to be inside the cutoff */
    sys.rx[0] = 1.0;
    sys.ry[0] = 1.0;
    sys.rz[0] = 1.0;
    sys.rx[1] = 1.5;
    sys.ry[1] = 1.5;
    sys.rz[1] = 1.5;
    sys.rx[2] = 2.0;
    sys.ry[2] = 2.0;
    sys.rz[2] = 2.0;
    
    /* set up the velocities to 0*/
    sys.vx[0] = 0.0;
    sys.vy[0] = 0.0;
    sys.vz[0] = 0.0;
    sys.vx[1] = 0.0;
    sys.vy[1] = 0.0;
    sys.vz[1] = 0.0;
    sys.vx[2] = 0.0;
    sys.vy[2] = 0.0;
    sys.vz[2] = 0.0;

    /* set up the forces */
    sys.fx[0] = 100.0;
    sys.fy[0] = 100.0;
    sys.fz[0] = 100.0;
    sys.fx[1] = 50.0;
    sys.fy[1] = 50.0;
    sys.fz[1] = 50.0;
    sys.fx[2] = -50.0;
    sys.fy[2] = -50.0;
    sys.fz[2] = -50.0;
    
    /* call the force routine */
    velverlet(&sys);
    
    /* check the results */
    /* positions updated */
    EXPECT_NEAR(sys.rx[0], 1.00209, 1e-5);
    EXPECT_NEAR(sys.ry[0], 1.00209, 1e-5);
    EXPECT_NEAR(sys.rz[0], 1.00209, 1e-5);
    EXPECT_NEAR(sys.rx[1], 1.50105, 1e-5);
    EXPECT_NEAR(sys.ry[1], 1.50105, 1e-5);
    EXPECT_NEAR(sys.rz[1], 1.50105, 1e-5);
    EXPECT_NEAR(sys.rx[2], 1.99895, 1e-5);
    EXPECT_NEAR(sys.ry[2], 1.99895, 1e-5);
    EXPECT_NEAR(sys.rz[2], 1.99895, 1e-5);

    /* velocities updated */
    EXPECT_NEAR(sys.vx[0], -0.00962, 1e-5);
    EXPECT_NEAR(sys.vy[0], -0.00962, 1e-5);
    EXPECT_NEAR(sys.vz[0], -0.00962, 1e-5);
    EXPECT_NEAR(sys.vx[1], 0.00951, 1e-5);
    EXPECT_NEAR(sys.vy[1], 0.00951, 1e-5);
    EXPECT_NEAR(sys.vz[1], 0.00951, 1e-5);
    EXPECT_NEAR(sys.vx[2], 0.02103, 1e-5);
    EXPECT_NEAR(sys.vy[2], 0.02103, 1e-5);
    EXPECT_NEAR(sys.vz[2], 0.02103, 1e-5);

    /* forces updated */
    EXPECT_NEAR(sys.fx[0], -145.99309, 1e-5);
    EXPECT_NEAR(sys.fy[0], -145.99309, 1e-5);
    EXPECT_NEAR(sys.fz[0], -145.99309, 1e-5);
    EXPECT_NEAR(sys.fx[1], -4.54038, 1e-5);
    EXPECT_NEAR(sys.fy[1], -4.54038, 1e-5);
    EXPECT_NEAR(sys.fz[1], -4.54038, 1e-5);
    EXPECT_NEAR(sys.fx[2], 150.53347, 1e-5);
    EXPECT_NEAR(sys.fy[2], 150.53347, 1e-5);
    EXPECT_NEAR(sys.fz[2], 150.53347, 1e-5);

    /* free the memory */
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}