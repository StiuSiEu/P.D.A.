#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


using namespace std;


int main(int argc, char **argv) {
	int rank;
	int size;
	int sum=0;
	int i,j,k;
	int a[4][4] =
	{
		{ 1, 9, 3, 9 },
		{ 2, 4, 1, 5 },
		{ 4, 4, 4, 4 },
		{ 1, 1, 1 ,1 }
	};
	int b[4][4] =
	{
		{ 1, 9, 3, 9 },
		{ 2, 4, 1, 5 },
		{ 4, 4, 4, 4 },
		{ 1, 1, 1 ,1 }
	};
	int c[4][4]= {
		{ 0, 0, 0, 0 },    // 40 66 33 75
		{ 0, 0, 0, 0 },	   // 19 43 19 47
		{ 0, 0, 0, 0 },    // 32 72 36 76
		{ 0, 0, 0, 0 }	   //  8 18  9 19
	};
	
	int recvBuffA[4];
	int sendBuffC[4];
	
	MPI_Status status;
	char hostname[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//	sursa, nr elemente trimise,tip elemente trimise,"destinatie",nr elemente ce ajung la destinatie, tip elemente destinatie,root-ul, comunicator?/
	MPI_Scatter(a, 16 / size, MPI_INT, recvBuffA, 16 / size, MPI_INT, 0, MPI_COMM_WORLD);
	
	MPI_Bcast(b, 16, MPI_INT, 0, MPI_COMM_WORLD);
	
	MPI_Barrier(MPI_COMM_WORLD);


	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			sum = sum + recvBuffA[j] * b[j][i];                 
		}
		sendBuffC[i] = sum;
		sum = 0;
	}
				
	MPI_Gather(sendBuffC, 16 / size, MPI_INT, c, 16/ size, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
	if (rank == 0)
	{
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				printf(" %d ", c[i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}