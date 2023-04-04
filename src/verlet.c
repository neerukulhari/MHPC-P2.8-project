#include "prototypes.h"
#include "constants.h"

// Split into two functions to avoid the overhead of function calls

void velverlet_propagation(mdsys_t* sys) 
{
// Propagate velocities by half and positions by full step
    int i;
    int N_atoms = sys->natoms;
    const double mass_factor = 0.5 * sys->dt / (mvsq2e * sys->mass);

    for (i = 0; i < N_atoms; ++i) 
    {
        sys->vx[i] += mass_factor * sys->fx[i];
        sys->vy[i] += mass_factor * sys->fy[i];
        sys->vz[i] += mass_factor * sys->fz[i];
        sys->rx[i] += sys->vx[i] * sys->dt;
        sys->ry[i] += sys->vy[i] * sys->dt;
        sys->rz[i] += sys->vz[i] * sys->dt;
    }
}

void velverlet_update(mdsys_t* sys) 
{
// Compute forces and potential energy
// Propagate velocities by another half step
    int i;
    int N_atoms = sys->natoms;

    const double mass_factor = 0.5 * sys->dt / (mvsq2e * sys->mass);

    for (i = 0; i < N_atoms; ++i) 
    {
        sys->vx[i] += mass_factor * sys->fx[i];
        sys->vy[i] += mass_factor * sys->fy[i];
        sys->vz[i] += mass_factor * sys->fz[i];
    }
}

void velverlet(mdsys_t* sys) 
{
    velverlet_propagation(sys);  // Propagate velocities by half and positions by full step
    force_optimized_3Law(sys);   // Compute forces and potential energy
    velverlet_update(sys); // Propagate velocities by another half step
}


// void verlet_test_1(mdsys_t* sys) {
// 	int i;

// 	for (i = 0; i < sys->natoms; ++i) {
// 		sys->vx[i] += 0.5 * sys->fx[i] / sys->mass;
// 		sys->rx[i] += sys->vx[i];
// 	}
// }

// void verlet_test_2(mdsys_t* sys) {
// 	int i;
// 	for (i = 0; i < sys->natoms; ++i) {
// 		sys->vx[i] += 0.5 * sys->fx[i] / sys->mass;
// 	}
// }


