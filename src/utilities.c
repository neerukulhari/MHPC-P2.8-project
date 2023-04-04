#include "utilities.h"
#include <sys/time.h>
#include <time.h>

/* helper function: get current time in seconds since epoch */
double wallclock() 
{
	struct timeval t; 
	gettimeofday(&t, 0);
	return ((double)t.tv_sec) + 1.0e-6 * ((double)t.tv_usec);
}

/* helper function: zero out an array */
// Loop unrolling 2x2 is applied for step+=2
void azzero(double* d, const int n) 
{       
    int i;
    for (i=0; i<n-1; i+=2) 
    {
        d[i]=0.0;
        d[i+1]=0.0;
    }
    if (i < n)
    {
        d[i]=0.0;
    }
}


/* helper function: apply minimum image convention */
double pbc(double x, const double boxby2)
{
    while (x >  boxby2) x -= 2.0*boxby2;
    while (x < -boxby2) x += 2.0*boxby2;
    return x;
}

/* allocate memory */
void allocate_mem(mdsys_t* const sys)
{
    // Allocating coordinates of atoms
	sys->rx = (double*)malloc(sys->natoms * sizeof(double));
	sys->ry = (double*)malloc(sys->natoms * sizeof(double));
	sys->rz = (double*)malloc(sys->natoms * sizeof(double));

	// Allocating velocities of atoms
	sys->vx = (double*)malloc(sys->natoms * sizeof(double));
	sys->vy = (double*)malloc(sys->natoms * sizeof(double));
	sys->vz = (double*)malloc(sys->natoms * sizeof(double));

	// Allocating forces of atoms
	sys->fx = (double*)malloc(sys->natoms * sizeof(double));
	sys->fy = (double*)malloc(sys->natoms * sizeof(double));
	sys->fz = (double*)malloc(sys->natoms * sizeof(double));

}

/* free memory */
void free_mem(mdsys_t* const sys) {
	// free coordinates
	free(sys->rx);
	free(sys->ry);
	free(sys->rz);
	// sys->rx = NULL;
	// sys->ry = NULL;
	// sys->rz = NULL;

	// free velocities
	free(sys->vx);
	free(sys->vy);
	free(sys->vz);
	// sys->vx = NULL;
	// sys->vy = NULL;
	// sys->vz = NULL;

	// free forces
	free(sys->fx);
	free(sys->fy);
	free(sys->fz);
	// sys->fx = NULL;
	// sys->fy = NULL;
	// sys->fz = NULL;

	
}

