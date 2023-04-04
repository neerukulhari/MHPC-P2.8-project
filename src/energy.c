//Computing Kinetic Energy

#include "prototypes.h"
#include "constants.h"
#ifdef _OPENMP
 #include <omp.h>
#endif

void ekin(mdsys_t *sys)
{
    #ifdef _OPENMP
    int Nthreads = omp_get_max_threads();
    #endif
    int i;
    double ekin=0.0;
    sys->ekin=0.0;
    double factor = 0.5 * mvsq2e * sys->mass;
    int N_atoms = sys->natoms;
    double factor_kb = 2.0/(3.0*N_atoms-3.0)/kboltz;
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(Nthreads) private(i) reduction(+:ekin) 
    #endif
    for (i=0; i<sys->natoms; ++i) {
        ekin += factor * (sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
    }
    sys->ekin = ekin;
    sys->temp = factor_kb*sys->ekin;
}
