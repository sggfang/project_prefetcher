#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>

#ifdef ONE
#define NUM_PROCESSES 1
#endif

#ifdef TWO
#define NUM_PROCESSES 2
#endif

#ifdef FOUR
#define NUM_PROCESSES 4
#endif

#ifdef EIGHT
#define NUM_PROCESSES 8
#endif

void create_arr(int N, int *arr){
		int i;
		srand(time(NULL));
		for (i=0;i<N;i++){
				arr[i] = rand()%N;
		} 
		// printf("create new array\n");
}

void merge(int *arr, int *temp_arr, int head_1, int head_2, int right){
		int index_1 = head_1;
		int index_2 = head_2 + 1;
		int temp_index = head_1;

		while(index_1<=head_2&&index_2<=right){
				if(arr[index_1]<=arr[index_2]){
						temp_arr[temp_index] = arr[index_1];
						index_1++;
				}else{
						temp_arr[temp_index] = arr[index_2];
						index_2++;
				}
				temp_index++;
		}

				if(index_1>head_2){
						int k;
						for(k=index_2;k<=right;k++){
								temp_arr[temp_index] = arr[k];
								temp_index++;
						}
				}else{
						int k;
						for(k=index_1;k<=head_2;k++){
								temp_arr[temp_index] = arr[k];
								temp_index++;
						}
				}
				
				int m;
				for(m=head_1;m<=right;m++){
						arr[m] = temp_arr[m];
				}
}

void merge_sort(int *arr, int *temp_arr, int left, int right){
		int mid;
		if (left<right){
				mid = (left+right)/2;
				merge_sort(arr, temp_arr, left, mid);
				merge_sort(arr, temp_arr, mid+1, right);
				merge(arr, temp_arr, left, mid, right);
		}
}

void sort(int N, int *arr){
		int myid;
		double begin_time, end_time, local_time;
		int process_num = NUM_PROCESSES;
		MPI_Comm_rank(MPI_COMM_WORLD, &myid);
		MPI_Comm_size(MPI_COMM_WORLD, &process_num);
		
		int sub_arr_size;
		if (N%process_num==0){
				sub_arr_size = N/process_num;
		}else{
				sub_arr_size = N/process_num + 1;
		}
		
		int *sub_arr;
		sub_arr = (int *)malloc(sub_arr_size*sizeof(int));
		MPI_Scatter(arr, sub_arr_size, MPI_INT, sub_arr, sub_arr_size, MPI_INT, 0, MPI_COMM_WORLD);
		
		begin_time = MPI_Wtime();

		int *temp_arr;
		temp_arr = (int *)malloc(sub_arr_size*sizeof(int));
		merge_sort(sub_arr, temp_arr, 0, sub_arr_size - 1);
		
		int *sorted_arr = NULL;
		if (myid==0){
				sorted_arr = (int *)malloc(N*sizeof(int));
		}
		MPI_Gather(sub_arr, sub_arr_size, MPI_INT, sorted_arr, sub_arr_size, MPI_INT, 0, MPI_COMM_WORLD);
		
		if (myid==0){
				int *other_arr;
				other_arr = (int *)malloc(N*sizeof(int));
				merge_sort(sorted_arr, other_arr, 0, N-1);
				free(sorted_arr);
				free(other_arr);
		}
		
		local_time = MPI_Wtime() - begin_time;
		MPI_Reduce(&local_time, &end_time, 1, MPI_DOUBLE,
		        		MPI_MAX, 0, MPI_COMM_WORLD);

		if(myid==0){
				printf("Total time: %f ms \n", end_time*1000);
		}

		free(arr);
		free(sub_arr);
		free(temp_arr);

		MPI_Barrier(MPI_COMM_WORLD);
}

/*
int main(int argc, char* argv[])
{
		int N[] = {10000, 100000, 1000000};
		int leng = 3;
		
		MPI_Init(&argc, &argv);

		int i;
		for (i=0;i<leng;i++){
				int arr_size = N[i];
				int *arr;
				arr = (int *)malloc(arr_size*sizeof(int));
				create_arr(arr_size, arr);
				sort(arr_size, arr);
		}

		MPI_Finalize();
    return 0;
}

*/
