#include "utilities.h"
#include <sys/time.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#ifdef _MPI
#include <mpi.h>
#endif

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
    #ifdef _OPENMP
    int Nthreads = omp_get_max_threads();
    #pragma omp parallel for num_threads(Nthreads) private(i)
    #endif
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

	// Allocating forces of atoms for MPI
    #ifdef _MPI
    sys->cx=(double *)malloc(sys->natoms*sizeof(double));
    sys->cy=(double *)malloc(sys->natoms*sizeof(double));
    sys->cz=(double *)malloc(sys->natoms*sizeof(double));
    #endif

}

/* free memory */
void free_mem(mdsys_t* const sys) {
	// free coordinates
	free(sys->rx);
	free(sys->ry);
	free(sys->rz);

	// free velocities
	free(sys->vx);
	free(sys->vy);
	free(sys->vz);

	// free forces
	free(sys->fx);
	free(sys->fy);
	free(sys->fz);

	// free MPI forces
    #ifdef _MPI
    free(sys->cx);
    free(sys->cy);
    free(sys->cz);
    MPI_Finalize();
    #endif
}

/* Fill the MPI and openMP struct parameters*/
void fill_struct(mdsys_t *sys)
{
    #ifdef _MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &(sys->mpirank));
    MPI_Comm_size(MPI_COMM_WORLD, &(sys->mpisize));
    #else
    sys->mpirank = 0;
    sys->mpisize = 1;
    #endif
    #ifdef _OPENMP
    sys->nthreads = omp_get_max_threads();
    #else
    sys->nthreads = 1;
    #endif
}

void broadcast_r_v(mdsys_t *sys)
{
    #ifdef _MPI
    /* broadcast from rank 0 to all other ranks */
    MPI_Bcast(sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->vx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->vy, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->vz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    #endif
}