//Computing Kinetic Energy

#include "prototypes.h"
#include "constants.h"

#ifdef _OPENMP
#include <omp.h>  
//int Nthreads = atoi(argv[1]);
#endif
void ekin(mdsys_t *sys)
{
    int i;

    sys->ekin=0.0;
    #pragma omp parallel for num_threads(Nthreads) private (i) reduction(+:sys->ekin)
    for (i=0; i<sys->natoms; ++i) {
        sys->ekin += 0.5*mvsq2e*sys->mass*(sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
    }
    sys->temp = 2.0*sys->ekin/(3.0*sys->natoms-3.0)/kboltz;
}

