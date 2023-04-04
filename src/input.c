#include "prototypes.h"
#include "structures.h"
#include "constants.h"
#ifdef _MPI
#include <mpi.h>
#endif

/* helper function: read a line and then return
   the first string with whitespace stripped off */
int get_a_line(FILE* fp, char* buf) {
	char tmp[BLEN], *ptr;

	/* read a line and cut of comments and blanks */
	if (fgets(tmp, BLEN, fp)) {
		int i;

		ptr = strchr(tmp, '#');
		if (ptr)
			*ptr = '\0';
		i = strlen(tmp);
		--i;
		while (isspace(tmp[i])) {
			tmp[i] = '\0';
			--i;
		}
		ptr = tmp;
		while (isspace(*ptr)) {
			++ptr;
		}
		i = strlen(ptr);
		strcpy(buf, tmp);
		return 0;
	} else {
		perror("problem reading input");
		return -1;
	}
	return 0;
}

int add_data(FILE* fp,
				  char (*line)[BLEN],
				  char (*restfile)[BLEN],
				  char (*trajfile)[BLEN],
				  char (*ergfile)[BLEN],
				  mdsys_t* sys,
				  int* nprint) {

	// Reads number of atoms from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	sys->natoms = atoi(*line);

	// Reads mass from fp and saves it in data_struct sys 
	if (get_a_line(fp, *line))
		return 1;
	sys->mass = atof(*line);

	// Reads epsilon which is the depth of the potential well from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	sys->epsilon = atof(*line);

	// Reads sigma which is the distance at which the potential is a minimum from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	sys->sigma = atof(*line);

	// Reads cutoff from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	sys->rcut = atof(*line);

	// Reads number of steps between printing to the trajectory file from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	sys->box = atof(*line);

	// Reads path/to/restart-file from fp and saves it in output array of char 'restfile'
	if (get_a_line(fp, *restfile))
		return 1;

	// Reads path/to/trajectories-file from fp and saves it in output array of char 'trajfile'
	if (get_a_line(fp, *trajfile))
		return 1;

	// Reads path/to/energies-file from fp and saves it in output array of char 'ergfile'
	if (get_a_line(fp, *ergfile))
		return 1;

	// Reads number of steps from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	sys->nsteps = atoi(*line);

	// Reads size of time step from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	sys->dt = atof(*line);

	// Reads box-size from fp and saves it in data_struct sys
	if (get_a_line(fp, *line))
		return 1;
	*nprint = atoi(*line);
	return 0;
}

void broadcast_data(mdsys_t* sys) {
    #ifdef _MPI
    /* broadcast from rank 0 to all other ranks */
    MPI_Bcast(&sys->natoms, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys->mass, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys->epsilon, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys->sigma, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys->rcut, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys->box, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys->nsteps, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys->dt, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    #endif
}