#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "structures.h"

/* this is needed to make the functions compatible with Googletest */
#ifdef __cplusplus
extern "C" {
#endif

double wallclock();
void azzero(double *d, const int n);
double pbc(double x, const double boxby2);

#ifdef __cplusplus
}
#endif
#endif