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

//IO functions
extern int get_a_line(FILE* fp, char* buf);
extern void output(mdsys_t* sys, FILE* erg, FILE* traj);
int add_data(FILE * fp, char (*line)[BLEN], char (*restfile)[BLEN], char (*trajfile)[BLEN], char (*ergfile)[BLEN], mdsys_t * sys, int * nprint);


//Force functions
extern void force(mdsys_t *sys);
extern void force_optimized(mdsys_t *sys);
extern void force_3Law(mdsys_t *sys);
extern void force_optimized_3Law(mdsys_t *sys);

//Energy functions
extern void ekin(mdsys_t *sys);

//Verlet functions
extern void velverlet_update(mdsys_t* sys);
extern void velverlet_propagation(mdsys_t* sys);
extern void velverlet(mdsys_t* sys);

// extern void verlet_test_1(mdsys_t *sys);
// extern void verlet_test_2(mdsys_t *sys);

#endif