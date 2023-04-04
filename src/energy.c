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
     #else
    int Nthreads = 1;
    #endif
    int i;
    double ekin=0.0;
    sys->ekin=0.0;
    #pragma omp parallel for num_threads(Nthreads) private(i) reduction(+:ekin) 
    for (i=0; i<sys->natoms; ++i) {
        ekin += 0.5*mvsq2e*sys->mass*(sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
    }
    sys->ekin = ekin;
    sys->temp = 2.0*sys->ekin/(3.0*sys->natoms-3.0)/kboltz;
}
