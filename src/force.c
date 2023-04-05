// Computing Foces

#include "prototypes.h"
#include "utilities.h"
#ifdef _OPENMP
#include <omp.h>
#endif
void force(mdsys_t *sys)
{
    double r, ffac;
    double rx, ry, rz;
    int i, j;

    /* zero energy and forces */
    sys->epot = 0.0;
    double epot = 0.0; /* local energy, will be summed over all nodes */
    azzero(sys->fx, sys->natoms);
    azzero(sys->fy, sys->natoms);
    azzero(sys->fz, sys->natoms);
    #ifdef _MPI
    azzero(sys->cx, sys->natoms);
    azzero(sys->cy, sys->natoms);
    azzero(sys->cz, sys->natoms);
    /* Broadcast the positions to all the nodes */
    MPI_Bcast(sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for (i = sys->mpirank; i < (sys->natoms); i += sys->mpisize)
    {
    #else
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(sys->nthreads) private(i,j,r,ffac,rx,ry,rz) reduction(+:epot)
    #endif
    for (i = 0; i < (sys->natoms); ++i)
    {
    #endif
        for (j = 0; j < (sys->natoms); ++j)
        {

            /* particles have no interactions with themselves */
            if (i == j)
                continue;

            /* get distance between particle i and j */
            rx = pbc(sys->rx[i] - sys->rx[j], 0.5 * sys->box);
            ry = pbc(sys->ry[i] - sys->ry[j], 0.5 * sys->box);
            rz = pbc(sys->rz[i] - sys->rz[j], 0.5 * sys->box);
            r = sqrt(rx * rx + ry * ry + rz * rz);

            /* compute force and energy if within cutoff */
            if (r < sys->rcut)
            {
                ffac = -4.0 * sys->epsilon * (-12.0 * pow(sys->sigma / r, 12.0) / r + 6 * pow(sys->sigma / r, 6.0) / r);

                epot += 0.5 * 4.0 * sys->epsilon * (pow(sys->sigma / r, 12.0) - pow(sys->sigma / r, 6.0));

                #ifdef _MPI
                sys->cx[i] += rx / r * ffac;
                sys->cy[i] += ry / r * ffac;
                sys->cz[i] += rz / r * ffac;
                #else
                sys->fx[i] += rx / r * ffac;
                sys->fy[i] += ry / r * ffac;
                sys->fz[i] += rz / r * ffac;
                #endif
            }
        }
    }
    #ifdef _MPI
    /* Collect the forces from all the nodes */
    MPI_Reduce(sys->cx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(sys->cy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(sys->cz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&epot, &sys->epot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    #else
    sys->epot = epot;
    #endif
}

// Optimized force function with precomputed constants and remove expensive sqrt() function call using third Newton Law
void force_optimized_3Law(mdsys_t *sys)
{
    double rx, ry, rz;
    int i, j;

    // Factors used in force calculation
    const double rcsq = sys->rcut * sys->rcut;
    const double sys_box = 0.5 * sys->box;
    const double epsilon = sys->epsilon;
    const double sigma = sys->sigma;
    const int N_atoms = sys->natoms;

    const double s6 = sigma * sigma * sigma * sigma * sigma * sigma;
    const double c6 = 4.0 * epsilon * s6;
    const double c12 = c6 * s6;

    // double factor for condition rsq < rcsq
    double r6, rsq, rinv, ffac;
    double F_x, F_y, F_z;

    /* zero energy and forces */
    sys->epot = 0.0;
    double epot = 0.0; /* local energy, will be summed over all nodes */

    azzero(sys->fx, N_atoms);
    azzero(sys->fy, N_atoms);
    azzero(sys->fz, N_atoms);

    #ifdef _MPI
    azzero(sys->cx, sys->natoms);
    azzero(sys->cy, sys->natoms);
    azzero(sys->cz, sys->natoms);
    /* Broadcast the positions to all the nodes */
    MPI_Bcast(sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (i = sys->mpirank; i < (sys->natoms); i += sys->mpisize)
    {
    #else
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(sys->nthreads) private(i,j,r,ffac,rx,ry,rz) reduction(+:epot)
    #endif
    for (i = 0; i < (sys->natoms - 1); ++i)
    {
    #endif
        for (j = i + 1; j < N_atoms; ++j)
        {
            /* particles have no interactions with themselves */
            if (i == j)
                continue;
            /* get distance between particle i and j */
            rx = pbc(sys->rx[i] - sys->rx[j], sys_box);
            ry = pbc(sys->ry[i] - sys->ry[j], sys_box);
            rz = pbc(sys->rz[i] - sys->rz[j], sys_box);
            rsq = (rx * rx + ry * ry + rz * rz);

            /* compute force and energy if within cutoff */
            if (rsq < rcsq)
            {
                rinv = 1.0 / rsq;
                r6 = rinv * rinv * rinv;

                ffac = 6.0 * r6 * (r6 * c12 * 2.0 - c6) * rinv;
                epot += r6 * (r6 * c12 - c6);

                F_x = ffac * rx;
                F_y = ffac * ry;
                F_z = ffac * rz;

                #ifdef _MPI
                sys->cx[i] += F_x;
                sys->cx[j] -= F_x;
                sys->cy[i] += F_y;
                sys->cy[j] -= F_y;
                sys->cz[i] += F_z;
                sys->cz[j] -= F_z;
                #else
                sys->fx[i] += F_x;
                sys->fx[j] -= F_x;
                sys->fy[i] += F_y;
                sys->fy[j] -= F_y;
                sys->fz[i] += F_z;
                sys->fz[j] -= F_z;
                #endif
            }
        }
    }
    #ifdef _MPI
    /* Collect the forces from all the nodes */
    MPI_Reduce(sys->cx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(sys->cy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(sys->cz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&epot, &sys->epot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    #else
    sys->epot = epot;
    #endif
}