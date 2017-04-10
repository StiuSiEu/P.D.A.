#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i,j,k;
	int a[5][5] = {
		{  0,   2, 99, 10 ,99 },
		{  2,   0,  3, 99 ,99 },
		{ 99,   3,  0,  1 , 8 },
		{ 10,  99,  1,  0 ,99 },
		{ 99,  99,  8, 99 , 0 }
	};
	
	int costMatrix[5][5];    
	/*
	  0  2  5 6 13
	  2	 0  3 4 11
	  5  3  0 1  8
	  6  4  1 0  9
	  13 11 8 9  0
	*/

	int numprocs, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
	for (k = 0; k < 5; k++)
	{
		for (i = rank; i < 5; i = i + numprocs)
		{
			for (j = 0; j < 5; j++)
			{
				if (a[i][j] > a[i][k] + a[k][j])
					
					a[i][j] = a[i][k] + a[k][j];
			}
		}
		
		MPI_Allreduce(a, costMatrix, 25, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
		
		for (i = 0; i < 5; i++)
			for (j = 0; j < 5; j++)
				a[i][j] = costMatrix[i][j];		
		
		MPI_Barrier(MPI_COMM_WORLD);
	}

	MPI_Finalize();

	if (rank == 0)
	{
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 5; j++)
			{
				printf("%d ", costMatrix[i][j]);
			}
			printf("\n");
		}
	}
		
}


