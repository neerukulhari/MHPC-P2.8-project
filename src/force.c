// Computing Foces

#include "prototypes.h"
#include "utilities.h"

void force(mdsys_t *sys) 
{
    double r,ffac;
    double rx,ry,rz;
    int i,j;

    /* zero energy and forces */
    sys->epot=0.0;
    azzero(sys->fx,sys->natoms);  // azzero is a function that sets all elements of an array to zero
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);

    for(i=0; i < (sys->natoms); ++i) {   // loop over all particles i and j
        for(j=0; j < (sys->natoms); ++j) {

            /* particles have no interactions with themselves */
            if (i==j) continue;

            /* get distance between particle i and j */
            rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            r = sqrt(rx*rx + ry*ry + rz*rz);

            /* compute force and energy if within cutoff */
            if (r < sys->rcut) {
                ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
                                         +6*pow(sys->sigma/r,6.0)/r);

                sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
                                               -pow(sys->sigma/r,6.0));

                sys->fx[i] += rx/r*ffac;
                sys->fy[i] += ry/r*ffac;
                sys->fz[i] += rz/r*ffac;
            }
        }
    }
}

// Optimized force function with precomputed constants and remove expensive sqrt() function call 
void force_optimized(mdsys_t* sys)
 {
	double r, ffac;
	double rx, ry, rz;
	int i, j;

    double sys_box;
	double factor;

    double F_x, F_y, F_z;
    double r6, rinv, rsq;
    double c12, c6, s6;

    double sigma = sys->sigma;
    double epsilon = sys->epsilon;
    int N_atoms = sys->natoms;
	

	/* zero energy and forces */
	sys->epot = 0.0;
	azzero(sys->fx, sys->natoms);
	azzero(sys->fy, sys->natoms);
	azzero(sys->fz, sys->natoms);

    // Precompute constants for force calculation 
	sys_box = 0.5 * sys->box;  // It is a half box length because of periodic boundary conditions 
	
	s6 = sigma * sigma * sigma * sigma * sigma * sigma;
	c6 = 4.0 * epsilon * s6;
	c12 = c6 * s6;
    
	for (i = 0; i < N_atoms; ++i) {
		for (j = 0; j < N_atoms; ++j) {
			/* particles have no interactions with themselves */
			if (i == j)
				continue;
			/* get distance between particle i and j */
			rx = pbc(sys->rx[i] - sys->rx[j], sys_box);
			ry = pbc(sys->ry[i] - sys->ry[j], sys_box);
			rz = pbc(sys->rz[i] - sys->rz[j], sys_box);
            rsq = rx * rx + ry * ry + rz * rz;
			r = sqrt(rsq);

			/* compute force and energy if within cutoff */
			if (r < sys->rcut) 
            {	
				rinv= 1.0 / (r * r);
				r6 = rinv * rinv * rinv;
				sys->epot +=  (c12 * r6  - c6 ) * r6 * 0.5;
				ffac = (12.0 * c12 * r6 - 6.0 * c6) * r6;
				factor = ffac * rinv;

            	F_x = factor * rx;
            	F_y = factor * ry;
            	F_z = factor * rz;


            	sys->fx[i] += F_x;
				sys->fy[i] += F_y;
				sys->fz[i] += F_z;

				
			}
		}
	}
}



// Compute forces with third Newton Law applied, more function modifications

void force_3Law(mdsys_t* sys)  //Fij = -Fji 
{
	double r, ffac;
	double rx, ry, rz;
	int i, j;

	/* zero energy and forces */
	sys->epot = 0.0;
	azzero(sys->fx, sys->natoms);
	azzero(sys->fy, sys->natoms);
	azzero(sys->fz, sys->natoms);

	for (i = 0; i < (sys->natoms) - 1; ++i) {
		for (j = i + 1; j < (sys->natoms); ++j) {
			// Particles have no interactions with themselves and they are symmetric
			if (i == j)
				continue;

			// Get distance between particle i and j and apply periodic boundary conditions
			rx = pbc(sys->rx[i] - sys->rx[j], 0.5 * sys->box);
			ry = pbc(sys->ry[i] - sys->ry[j], 0.5 * sys->box);
			rz = pbc(sys->rz[i] - sys->rz[j], 0.5 * sys->box);
			r = sqrt(rx * rx + ry * ry + rz * rz);
                        

			/* compute force and energy if within cutoff */
			if (r < sys->rcut) {
				ffac = -4.0 * sys->epsilon *(-12.0 * pow(sys->sigma / r, 12.0) / r + 6 * pow(sys->sigma / r, 6.0) / r);

				sys->epot += 0.5 * 4.0 * sys->epsilon *(pow(sys->sigma / r, 12.0) - pow(sys->sigma / r, 6.0));

				sys->fx[i] += rx / r * ffac;
				sys->fx[j] -= rx / r * ffac;
				sys->fy[i] += ry / r * ffac;
				sys->fy[j] -= ry / r * ffac;
				sys->fz[i] += rz / r * ffac;
				sys->fz[j] -= rz / r * ffac;
			}
		}
	}
}

// Optimized force function with precomputed constants and remove expensive sqrt() function call using third Newton Law
void force_optimized_3Law(mdsys_t* sys) {
	double rx, ry, rz;
	int i, j;

    // Factors used in force calculation   
    const double rcsq = sys->rcut * sys->rcut;
    const double sys_box= 0.5 * sys->box;
    const double epsilon = sys->epsilon;
	const double sigma = sys->sigma;
    const int N_atoms = sys->natoms;

    const double s6 = sigma * sigma * sigma * sigma * sigma * sigma;
    const double c6 = 4.0 * epsilon * s6;
	const double c12 = c6 * s6;

    //double factor for condition rsq < rcsq
    double r6, rsq, rinv, ffac;
    double F_x, F_y, F_z;

	/* zero energy and forces */
	sys->epot = 0.0;
        
	azzero(sys->fx, N_atoms);
	azzero(sys->fy, N_atoms);
	azzero(sys->fz, N_atoms);
	
	for (i = 0; i < (N_atoms - 1); ++i) {
		for (j = i + 1; j < N_atoms; ++j) {
			/* particles have no interactions with themselves */
			if (i == j)
				continue;
			/* get distance between particle i and j */
			rx = pbc(sys->rx[i] - sys->rx[j], sys_box);
			ry = pbc(sys->ry[i] - sys->ry[j], sys_box);
			rz = pbc(sys->rz[i] - sys->rz[j], sys_box);
			rsq = (rx * rx + ry * ry + rz * rz);
        

			/* compute force and energy if within cutoff */
			if (rsq < rcsq) {
                rinv = 1.0 / rsq;
				r6 = rinv * rinv * rinv;
				
				ffac = 6.0* r6 * ( r6 * c12 * 2.0 - c6 ) * rinv;
                sys->epot += r6 * (r6* c12 - c6);
				                                
            	F_x = ffac * rx ;
            	sys->fx[i] += F_x;
				sys->fx[j] -= F_x;

                F_y = ffac * ry ;
				sys->fy[i] += F_y;
				sys->fy[j] -= F_y;

                F_z = ffac * rz ;
				sys->fz[i] += F_z;
				sys->fz[j] -= F_z;
				
			}
		}
	}
}