
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__device__ int get_index_to_check(int thread, int num_threads, int set_size, int offset) {

	// Integer division trick to round up
	return (((set_size + num_threads) / num_threads) * thread) + offset;
}

// Device code
__global__ void p_ary_search(int search, int array_length, int *arr, int *ret_val)
{
	const int num_threads = blockDim.x * gridDim.x;
	const int thread = blockIdx.x * blockDim.x + threadIdx.x;
	int set_size = array_length;
	
	ret_val[0] = -1; 
	ret_val[1] = 0; 

	while (set_size != 0)
	{
		int offset = ret_val[1];

		__syncthreads();

		// Get the next index to check
		int index_to_check = get_index_to_check(thread, num_threads, set_size, offset);

		// If the index is outside the bounds of the array do not check it
		if (index_to_check < array_length)
		{
			// If the next index is outside the bounds of the array, then set it to maximum array size
			int next_index_to_check = get_index_to_check(thread + 1, num_threads, set_size, offset);
				if (next_index_to_check >= array_length)
				{
					next_index_to_check = array_length - 1;
				}

				// If we're at the mid section of the array reset the offset to this index
				if (search > arr[index_to_check] && (search < arr[next_index_to_check]))
				{
					ret_val[1] = index_to_check;
				}
				else if (search == arr[index_to_check])
				{
					// Set the return var if find it
					ret_val[0] = index_to_check;
				}
		}

		// Since this is a paralel array search divide by our total threads to get the next set size
		set_size = set_size / num_threads;

		// Sync up so no threads jump ahead
		__syncthreads();
	}
}

// Host code
int main()
{
	int N = 23;
	size_t size = N * sizeof(int);
	
	int search=5;
	
	//int h_result;
	int *h_result = (int*)malloc(sizeof(int) * 2);
	int *d_result;
	cudaMalloc((void**)&d_result, sizeof(int) * 2);

	cudaMemcpy(d_result, &h_result, sizeof(int), cudaMemcpyHostToDevice);

	// Allocate input vector h_A in host memory
	int* h_A = (int*)malloc(size);
	// Initialize input vectors
	for (int i = 0;i < N;i++)
	{
		h_A[i] = i;
	}
	// Allocate vector in device memory
	int* d_A;
	cudaMalloc(&d_A, size);
	
	// Copy vectors from host memory to device memory
	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);


	// Invoke kernel
	p_ary_search << <16, 64 >> >(search, N, d_A, d_result);
	

	// Copy result from device memory to host memory h_C contains the result in host memory
	cudaMemcpy(h_result, d_result, 2 * sizeof(int), cudaMemcpyDeviceToHost);
	
	
	printf("the result is :%d", h_result[0]);

	// Free device memory
	/*cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	*/
	scanf("%d", N);
}

