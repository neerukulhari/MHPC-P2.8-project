#include "prototypes.h"
#ifdef _OPENMP
#include <omp.h>
#endif

/* append data to output. */
void output(mdsys_t* sys, FILE* erg, FILE* traj)
{ 
    #ifdef _OPENMP
    int Nthreads = omp_get_max_threads();
    #else
      int Nthreads = 1;
    #endif
    int i;

    printf("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", sys->nfi, sys->temp, sys->ekin, sys->epot, sys->ekin+sys->epot);
    fprintf(erg,"% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", sys->nfi, sys->temp, sys->ekin, sys->epot, sys->ekin+sys->epot);
    fprintf(traj,"%d\n nfi=%d etot=%20.8f\n", sys->natoms, sys->nfi, sys->ekin+sys->epot);
    #pragma omp parallel for num_threads(Nthreads) private(i)
    for (i=0; i<sys->natoms; ++i) {
        fprintf(traj, "Ar  %20.8f %20.8f %20.8f\n", sys->rx[i], sys->ry[i], sys->rz[i]);
    }
}
