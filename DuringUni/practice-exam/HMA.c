#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

#define debug 1

typedef struct worker_args{
	float * array;
	int w;
	int h;
	int x;
	int y;
}worker_args;

// gcc -Wall -Wvla -Werror -std=gnu11 -Werror=format-security -lm -pthread hma.c -o hma
void* calculate_center(void* args){
	worker_args* wargs = args;

	float* array = wargs->array;
	int w = wargs->w;
	int h = wargs->h;
	int x = wargs->x;
	int y = wargs->y;

	float* average = calloc(1, sizeof(float));

	for (int i = -1; i <= 1; i++){
		y += i;
		
		for (int j = -1; j <= 1; j++){
			x += j;
			
			// if the values are not out of bounds
			if (x < w && x > 0 && y < h && y > 0){
				(*average) += array[x + y*w];
			}
		}
	}

	(*average) /= 9.0;
	return average;
}

void get_hma_parallel(int nthreads, float * array, int w, int h, int * found_x, int * found_y) {
	// pre : w > 0 h > 0
	// returns the position of the highest magnitude average of the array
	// in variables found_x and found_y
	if (array == NULL || w <= 0 || h <= 0)
		return;

	float highest = -FLT_MAX;

	pthread_t* threads = malloc(sizeof(pthread_t) * nthreads);

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			worker_args* args = malloc(sizeof(worker_args));
			args->array = array;
			args->w = w;
			args->h = h;
			args->x = j;
			args->y = i;
			pthread_create(&threads[i + j*w], NULL, &calculate_center, args);
		}
	}

	for (int i = 0; i < w*h; i++){
		for (int j = 0; j < w; j++){
			int* average;
			pthread_join(threads[i + j*w], (void**) &average);

			if ((*average) > highest){
				highest = (*average); 
				(*found_x) = j;
				(*found_y) = i;
				free(average);
			}
		}
	}

	free(threads);
}

void get_hma (float * array, int w, int h, int * found_x, int * found_y) {
	// pre : w > 0 h > 0
	// returns the position of the highest magnitude average of the array
	// in variables found_x and found_y
	if (array == NULL || w <= 0 || h <= 0)
		return;

	float highest = -FLT_MAX;

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			worker_args args = {.array = array, .w = w, .h = h, .x = j , .y = i};
			float* average = calculate_center(&args);

			if ( (*average) > highest){
				highest = (*average); 
				(*found_x) = j;
				(*found_y) = i;
			}
			free(average);
		}
	}
}

int student_main(int argc, char **argv)
{
	int x, y;
	float array[9] = {1,2,3,4,5,6,7,8,9};
	
	get_hma(array, 3, 3, &x, &y);
	printf("x = %d y = %d\n",x,y);
	// get_hma_parallel(9, array, 3, 3, &x, &y);
	// printf("x = %d y = %d\n",x,y);

    return 0;
}


/*
 * DO NOT MODIFY THIS MAIN FUNCTION
 */
int main(int argc, char **argv) // #151479
{
    return student_main(argc, argv);
}
