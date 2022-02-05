#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//#define DEBUG

#ifdef DEBUG
#define NUM_THREADS 2 
#endif

#ifdef ONE
#define NUM_THREADS 1
#endif

#ifdef TWO
#define NUM_THREADS 2
#endif

#ifdef FOUR
#define NUM_THREADS 4
#endif

#ifdef EIGHT
#define NUM_THREADS 8
#endif

#ifdef SIXTEEN
#define NUM_THREADS 16
#endif

struct members{
		int from;
		int to;
		double *a;
		double *b;
		double *c;
		int N;
};

void create_mat(int x, int y, double* mat){
		int i, j;
		for (i = 0; i < x; i++){
				for (j=0;j<y;j++){
						mat[i*x+j] = 1;
				}
		}
}

void* init_mat(void* args){
		int i, j;
		struct members *temp;
		temp = (struct members *)args;
   for(i=temp->from; i<=temp->to; i++) {
			for(j=0;j<temp->N;j++){
     		temp->c[i*temp->N+j] = 0;
			}
   }
}

void* do_calc(void *args){
		int i, k, j;
		struct members *temp;
		temp = (struct members *)args;
		for(i=temp->from;i<=temp->to;i++){
				for(k=0;k<temp->N;k++){
						for(j=0;j<temp->N;j++){
								temp->c[i*temp->N+j] += temp->a[i*temp->N+k] * temp->b[k*temp->N+j];
						}
				}
		}
}

void matmult(int N, double *a, double *b, double *c) {
		printf("Thread number: %d\n", NUM_THREADS);
   int i =0;
   pthread_t worker_threads[NUM_THREADS];
	 int block_size = 0;
		struct timespec start, finish;
		double elapsed;	

	 if (N%NUM_THREADS!=0){
			block_size = N/NUM_THREADS + 1;
	 }else{
			block_size = N/NUM_THREADS;
	 }

		clock_gettime(CLOCK_MONOTONIC, &start);

		// Initialize matrix C to 0
   for(i=0; i< NUM_THREADS; i++) {
			struct members *args;
			args = (struct members *)malloc(sizeof(struct members));
			if (block_size*(i+1)>N) args->to = N-1;
			else args->to = block_size*(i+1) - 1;
			args->from = i*block_size;
			args->a = a;
			args->b = b;
			args->c = c;
			args->N = N;
     if(pthread_create(&worker_threads[i], NULL, init_mat, (void *)args)) {
       fprintf(stderr, "Error creating thread %d\n",i);
     }
   }
   for(i=0; i< NUM_THREADS; i++) {
     pthread_join(worker_threads[i], NULL); 
   }
		
		// Do the calculation
   for(i=0; i< NUM_THREADS; i++) {
			struct members *args;
			args = (struct members *)malloc(sizeof(struct members));
			if (block_size*(i+1)>N) args->to = N-1;
			else args->to = block_size*(i+1) - 1;
			args->from = i*block_size;
			args->a = a;
			args->b = b;
			args->c = c;
			args->N = N;
		 if(pthread_create(&worker_threads[i], NULL, do_calc, (void *)args)) {
       fprintf(stderr, "Error creating thread %d\n",i);
     }
   }
   for(i=0; i< NUM_THREADS; i++) {
     pthread_join(worker_threads[i], NULL); 
   }

		clock_gettime(CLOCK_MONOTONIC, &finish);

		elapsed = (finish.tv_sec - start.tv_sec)*1000;
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000.0;
/*
		for (i=0;i<N;i++){
				int j;
				for(j=0;j<N;j++){
						printf("%5.6f\t", *(c+i*N+j));
				}
				printf("\n");
		}
		*/
		printf("Total time: %5.6f ms\n", elapsed);
}

/*
int main(){
		int N[] = {128, 512, 1000};
		int i;
		int leng = 3;
		for (i=0;i<leng;i++){
				int mat_size = N[i];
				double *a;
				a = (double *)malloc(mat_size*mat_size*sizeof(double));
				create_mat(mat_size, mat_size, a);
				double *b;
				b = (double *)malloc(mat_size*mat_size*sizeof(double));
				create_mat(mat_size, mat_size, b);

				double *c;
				c = (double *)malloc(mat_size*mat_size*sizeof(double));
				matmult(mat_size, a, b, c);
		}
		return 0;
}
*/