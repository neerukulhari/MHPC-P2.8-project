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
void azzero(double* d, const int n) 
{       
    int i;
    for (i=0; i<n; ++i) 
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

/* Fill the MPI struct parameters*/
void fill_mpi_struct(mdsys_t *sys)
{
    #ifdef _MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &(sys->mpirank));
    MPI_Comm_size(MPI_COMM_WORLD, &(sys->mpisize));
    #else
    sys->mpirank = 0;
    sys->mpisize = 1;
    #endif
}