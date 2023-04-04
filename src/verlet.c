#include "prototypes.h"
#include "constants.h"
#ifdef _OPENMP
 #include <omp.h>
#endif

/* velocity verlet propagation step*/
void velverlet(mdsys_t *sys) 
{
    #ifdef _OPENMP
      int Nthreads = omp_get_max_threads();
     #else
        int Nthreads = 1;
    #endif
    int i;

    /* first part: propagate velocities by half and positions by full step */
   #pragma omp parallel for num_threads(Nthreads) private(i)
    for (i=0; i<sys->natoms; ++i) {
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
        sys->rx[i] += sys->dt*sys->vx[i];
        sys->ry[i] += sys->dt*sys->vy[i];
        sys->rz[i] += sys->dt*sys->vz[i];
    }

    /* compute forces and potential energy */
    force(sys);

    /* second part: propagate velocities by another half step */
    #pragma omp parallel for num_threads(Nthreads) private(i)
    for (i=0; i<sys->natoms; ++i) {
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
    }
}