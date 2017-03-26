#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define MASTER 0
using namespace std;


int main(int argc, char **argv) {
	int rank;
	int size;	//	  0 1 2 3 4  5 6  7  8  9
	int array[10] = { 1,2,3,4,10,9,55,11,12,8 };
	int i = 0, j = 0;
	int lookingFor = 10;
	int found = 0;
	int wasItFound = 0;
	MPI_Status status;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//cout << "Hello, I'm process " << rank<< " of " << size << endl;
	if (rank != 5)
	{
		if (array[rank] == lookingFor)
		{
			found = 1;
			cout << "proccess " << rank << " found the value at index " << rank << "\n";
			MPI_Send(&found, 1, MPI_INT, 5, 666, MPI_COMM_WORLD);
		}
		else
			if (array[rank + size] == lookingFor)
			{
				found = 1;
				cout << "proccess " << rank << " found the value at index " << rank + size << "\n";
				MPI_Send(&found, 1, MPI_INT, 5, 666, MPI_COMM_WORLD);
			}
			else
			{
				found = 0;
				//cout << "Sry m8, it doesent exist";
				MPI_Send(&found, 1, MPI_INT, 5, 666, MPI_COMM_WORLD);
			}
	}
	else
		if(rank==5)
	{
		MPI_Recv(&wasItFound, 1, MPI_INT, 0, 666, MPI_COMM_WORLD, &status);
		MPI_Recv(&wasItFound, 1, MPI_INT, 1, 666, MPI_COMM_WORLD, &status);
		MPI_Recv(&wasItFound, 1, MPI_INT, 2, 666, MPI_COMM_WORLD, &status);
		MPI_Recv(&wasItFound, 1, MPI_INT, 3, 666, MPI_COMM_WORLD, &status);
		MPI_Recv(&wasItFound, 1, MPI_INT, 4, 666, MPI_COMM_WORLD, &status);

		if(wasItFound==0)
		{
			cout << "Could not find the element";
		}
	}

	MPI_Finalize();
	return 0;
}