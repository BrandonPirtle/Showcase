/*H**********************************************************************
* FILENAME :	hello.c
*
* DESCRIPTION :
*       Exhibits most basic use of MPI
*
* NOTES :
*       Execute using mpiexec
* 
* AUTHOR :    Brandon Pirtle        START DATE :    30 Oct 17
*									EDIT  DATE :	13 Dec 17
*
*H*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int npes, myrank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("From process %d out of %d, Hello World!\n", myrank, npes);
	MPI_Finalize();
}