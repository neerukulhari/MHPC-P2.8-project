#include "prototypes.h"
#include "constants.h"

/* velocity verlet propagation step*/
void velverlet(mdsys_t *sys) 
{
    const double factor = 0.5 * sys->dt / (mvsq2e * sys->mass);
    int N_atoms = sys->natoms;
    int i;
	for (i = 0; i < N_atoms; ++i) {
		sys->vx[i] += factor * sys->fx[i];
		sys->vy[i] += factor * sys->fy[i];
		sys->vz[i] += factor * sys->fz[i];
		sys->rx[i] += sys->dt * sys->vx[i];
		sys->ry[i] += sys->dt * sys->vy[i];
		sys->rz[i] += sys->dt * sys->vz[i];
	}

/* compute forces and potential energy */
force(sys);

/* second part: propagate velocities by another half step */
for (i=0; i< N_atoms; ++i) {
    sys->vx[i] += factor * sys->fx[i];
    sys->vy[i] += factor * sys->fy[i];
    sys->vz[i] += factor * sys->fz[i];
    }

}

