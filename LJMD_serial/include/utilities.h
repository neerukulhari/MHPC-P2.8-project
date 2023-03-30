#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "structures.h"


#ifdef __cplusplus
extern "C"
{
#endif

extern double wallclock();
extern void azzero(double *d, const int n);
extern double pbc(double x, const double boxby2);

#ifdef __cplusplus
}
#endif

#endif