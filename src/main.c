/*
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 * baseline c version.
 */
#include "prototypes.h"
#include "utilities.h"

/* main */
int main(int argc, char **argv)
{
    int nprint, i;
    char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
    FILE *fp,*traj,*erg;
    mdsys_t sys;
    double t_start;

    #ifdef _MPI
    MPI_Init(NULL, NULL);
    #endif
    fill_mpi_struct(&sys);
    
    if (sys.mpirank==0) printf("LJMD version %3.1f\n", LJMD_VERSION);

    t_start = wallclock();

    /* read input file */
    add_data(stdin, &line, &restfile, &trajfile, &ergfile, &sys, &nprint);
    #ifdef _MPI
    /* broadcast from rank 0 to all other ranks */
    MPI_Bcast(&sys.natoms, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys.mass, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys.epsilon, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys.sigma, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys.rcut, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys.box, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys.nsteps, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sys.dt, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    #endif

    /* allocate memory */

    allocate_mem(&sys);

    #ifdef _MPI
    sys.cx=(double *)malloc(sys.natoms*sizeof(double));
    sys.cy=(double *)malloc(sys.natoms*sizeof(double));
    sys.cz=(double *)malloc(sys.natoms*sizeof(double));
    #endif


    if(sys.mpirank==0) {
        /* read restart */
        fp=fopen(restfile,"r");
        if(fp) {
            for (i=0; i<sys.natoms; ++i) {
                fscanf(fp,"%lf%lf%lf",sys.rx+i, sys.ry+i, sys.rz+i);
            }
            for (i=0; i<sys.natoms; ++i) {
                fscanf(fp,"%lf%lf%lf",sys.vx+i, sys.vy+i, sys.vz+i);
            }
            fclose(fp);
            azzero(sys.fx, sys.natoms);
            azzero(sys.fy, sys.natoms);
            azzero(sys.fz, sys.natoms);
        } else {
            perror("cannot read restart file");
            return 3;
        }
    }
    #ifdef _MPI
    /* broadcast from rank 0 to all other ranks */
    MPI_Bcast(sys.rx, sys.natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys.ry, sys.natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys.rz, sys.natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys.vx, sys.natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys.vy, sys.natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys.vz, sys.natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    #endif

    /* initialize forces and energies.*/
    sys.nfi=0;

    force_optimized_3Law(&sys);
    
    if (sys.mpirank==0) {
        ekin(&sys);

        erg=fopen(ergfile,"w");
        traj=fopen(trajfile,"w");

        printf("Startup time: %10.3fs\n", wallclock()-t_start);
        printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);
        printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
        output(&sys, erg, traj);
    }

    /* reset timer */
    t_start = wallclock();

    /**************************************************/
    /* main MD loop */
    for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

        /* write output, if requested */
        if ((sys.nfi % nprint) == 0 && sys.mpirank==0)
            output(&sys, erg, traj);

        /* propagate system and recompute energies */
        velverlet(&sys);
        if (sys.mpirank==0) ekin(&sys);

    }
    /**************************************************/
    if (sys.mpirank==0) {
        /* clean up: close files, free memory */
        printf("Simulation Done. Run time: %10.3fs\n", wallclock()-t_start);
        fclose(erg);
        fclose(traj);
    }

    free_mem(&sys);
    #ifdef _MPI
    free(sys.cx);
    free(sys.cy);
    free(sys.cz);
    MPI_Finalize();
    #endif
    return 0;
}