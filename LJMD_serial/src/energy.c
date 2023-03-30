//Computing Kinetic Energy

#include "prototypes.h"
#include "constants.h"

void ekin(mdsys_t *sys)
{
    int i;

    sys->ekin=0.0;
    int N_atoms = sys->natoms;
    double factor = 0.5*mvsq2e*sys->mass;
    double f_temp= (2.0/((3.0*N_atoms-3.0)*kboltz));
    for (i=0; i<N_atoms; ++i) {
        sys->ekin += factor*(sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
    }
    sys->temp = f_temp*sys->ekin;
}

