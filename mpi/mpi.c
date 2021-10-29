/* Dummy MPI program for testing (based on https://mpitutorial.com/tutorials/mpi-send-and-receive/) */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int
main(int argc, char *argv[])
{
	int	rank;
	int	size;
	int	i;
	int	val;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Rank %i is running on host %s\n", rank, getenv("HOSTNAME"));
	if (rank == 0) {
		for (i = 1; i < size; ++i) {
			val = rand();
			printf("Rank 0 sending %i to rank %i\n", val, i);
			MPI_Send(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
		    MPI_STATUS_IGNORE);
		printf("Rank %i got %i from rank 0\n", rank, val);
	}
	MPI_Finalize();
	return 0;
}
