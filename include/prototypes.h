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

/* this is needed to make the functions compatible with Googletest */
#ifdef __cplusplus
extern "C" {
#endif

//IO functions
int get_a_line(FILE *fp, char *buf);
void output(mdsys_t *sys, FILE *erg, FILE *traj);

//Force functions
void force(mdsys_t *sys);

//Energy functions
void ekin(mdsys_t *sys);

//Verlet functions
void velverlet(mdsys_t *sys);

#ifdef __cplusplus
}
#endif
#endif