#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define MASTER 0
using namespace std;


int main(int argc, char **argv) {
	int rank;
	int size;	
	int array[10]; 
	int i = 0;
	int lookingFor = 9;
	int realMaxPos = 0;
	int maxPos=0;

	MPI_Status status;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) 
	{
		for (int i = 0; i < 10; i++)
		{
			array[i] = i;
		}
		array[8] = 9;
		//0 1 2 3 4 5 6 7 9 9
	}
	MPI_Bcast(array, 10, MPI_INT, 0, MPI_COMM_WORLD);
	for (i = rank;i < 10;i = i + size)
	{
		if (array[i] == lookingFor)
		{
			maxPos = i;
		}
	}
	
	MPI_Reduce(&maxPos, &realMaxPos, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		cout << "The maximum position is :" << realMaxPos<<"\n";
	}

	MPI_Finalize();

	return 0;
}