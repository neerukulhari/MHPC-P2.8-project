#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "structures.h"

#ifdef _MPI
#include <mpi.h>
#endif

/* this is needed to make the functions compatible with Googletest */
#ifdef __cplusplus
extern "C" {
#endif

extern double wallclock();
extern void azzero(double* d, const int n);
extern double pbc(double x, const double boxby2);
extern void allocate_mem(mdsys_t* const sys);
extern void free_mem(mdsys_t* const sys);
extern void fill_struct(mdsys_t *sys);
extern void broadcast_r_v(mdsys_t *sys);

#ifdef __cplusplus
}
#endif
#endif