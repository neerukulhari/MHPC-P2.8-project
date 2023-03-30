#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "structures.h"

double wallclock();
void azzero(double *d, const int n);
double pbc(double x, const double boxby2);

#endif