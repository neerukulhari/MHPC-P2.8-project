#include "utilities.h"
#include <sys/time.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

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
    #ifdef _OPENMP
      int Nthreads = omp_get_max_threads();
    #else
        int Nthreads = 1;
     #endif
    int i;
    #pragma omp parallel for num_threads(Nthreads) private(i)
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


