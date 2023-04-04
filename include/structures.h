#ifndef STRUCTURES_H
#define STRUCTURES_H

/* structure to hold the complete information
 * about the MD system */
struct _mdsys
{
    int nfi, nsteps, natoms, nsize;
	double dt, mass, epsilon, box, sigma, rcut;
	double ekin, temp, epot;
	double *rx, *ry, *rz;
	double *vx, *vy, *vz;
	double *fx, *fy, *fz;
};
typedef struct _mdsys mdsys_t;

#endif