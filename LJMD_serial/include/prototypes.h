#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "structures.h"
#include "constants.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C"
{
#endif

//IO functions
extern int get_a_line(FILE *fp, char *buf);
extern void output(mdsys_t *sys, FILE *erg, FILE *traj);

//Force functions
extern void force(mdsys_t *sys);

//Energy functions
extern void ekin(mdsys_t *sys);

//Verlet functions
extern void velverlet(mdsys_t *sys);


#ifdef __cplusplus
}
#endif

#endif