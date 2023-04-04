#include "prototypes.h"
#include "constants.h"
#ifdef _OPENMP
#include <omp.h>
#endif


// Split into two functions to avoid the overhead of function calls
void velverlet_propagation(mdsys_t* sys) 
{
// Propagate velocities by half and positions by full step
    #ifdef _OPENMP
    int Nthreads = omp_get_max_threads();
    #endif
    int i;
    int N_atoms = sys->natoms;
    const double mass_factor = 0.5 * sys->dt / (mvsq2e * sys->mass);

    #ifdef _OPENMP
    #pragma omp parallel for num_threads(Nthreads) private(i)
    #endif
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
    #ifdef _OPENMP
    int Nthreads = omp_get_max_threads();
    #endif
    int i;
    int N_atoms = sys->natoms;

    const double mass_factor = 0.5 * sys->dt / (mvsq2e * sys->mass);

    #ifdef _OPENMP
    #pragma omp parallel for num_threads(Nthreads) private(i)
    #endif
    for (i = 0; i < N_atoms; ++i) 
    {
        sys->vx[i] += mass_factor * sys->fx[i];
        sys->vy[i] += mass_factor * sys->fy[i];
        sys->vz[i] += mass_factor * sys->fz[i];
    }
}

void velverlet(mdsys_t* sys) 
{
    if (sys->mpirank==0) velverlet_propagation(sys);  // Propagate velocities by half and positions by full step
    force_optimized_3Law(sys);   // Compute forces and potential energy
    if (sys->mpirank==0) velverlet_update(sys); // Propagate velocities by another half step
}
