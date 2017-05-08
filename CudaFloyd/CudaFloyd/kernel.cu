
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

#define N 5

__global__ void RoyFloyd(int a[N][N], int k)
{
	int i = threadIdx.x;
	int j = threadIdx.y;

	if (a[i][j] > a[i][k] + a[k][j])
		a[i][j] = a[i][k] + a[k][j];
}


int main()
{
	int h_a[N][N] = {
		{ 0,   2, 99, 10 ,99 },
		{ 2,   0,  3, 99 ,99 },
		{ 99,   3,  0,  1 , 8 },
		{ 10,  99,  1,  0 ,99 },
		{ 99,  99,  8, 99 , 0 }
	};

	int h_c = 0;
	size_t size = N * N * sizeof(int);
	int *d_a;
	//int *d_c;
	cudaMalloc(&d_a, size);
//	cudaMalloc(&d_c, sizeof(int));

	int numBlocks = 1;
	dim3 threadsPerBlock(N, N);

	cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);


	for (h_c = 0; h_c < N; h_c++) {
		//cudaMemcpy(d_c, &h_c, sizeof(int), cudaMemcpyHostToDevice);
		RoyFloyd << <1, threadsPerBlock >> > (d_a, h_c);
	}

	cudaMemcpy(h_a, d_a, size, cudaMemcpyDeviceToHost);

	for (int i = 0;i <= N;i++)
	{
		for (int j = 0;j <= N;j++)
		{
			printf("%d ", h_a[i][j]);
		}
		printf("\n");
	}
	cudaFree(d_a);
//	cudaFree(d_c);
	return 0;
}
