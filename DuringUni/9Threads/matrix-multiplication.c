#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 512
// the resulting matrix is a row entry 2D array, not an actual matrix
#define IDX(x, y) ((x) + (y)*WIDTH)

#define NTHREADS 4

struct worker_args {
    int id;
    int* a;
    int* b;
    int* result;
};

void* multiply_worker(void* arg) {
    // unpack args
    struct worker_args* wargs = arg;
    int* a = wargs->a;
    int* b = wargs->b;
    int* result = wargs->result;
    int id = wargs->id;

	//calculates which section of the matrix the thread will be working on based on how many threads there are	
    int chunk = WIDTH/NTHREADS;

	// manipulates the indexes the worker will be accessing in the y coordinate (essentially the column)
    for (size_t y = id*chunk; y < (id+1)*chunk; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            for (size_t k = 0; k < WIDTH; k++) {
                result[IDX(x, y)] += a[IDX(k, y)] * b[IDX(x, k)];
            }
        }
    }
    return NULL;
}

/**
 * Returns the matrix multiplication of a and b.
 */
int* naive_multiply(const int* a, const int* b) {
    int* result = calloc(WIDTH * WIDTH, sizeof(int));
    for (size_t y = 0; y < WIDTH; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            for (size_t k = 0; k < WIDTH; k++) {
                result[IDX(x, y)] += a[IDX(k, y)] * b[IDX(x, k)];
            }
        }
    }
    return result;
}

int* generate_random_matrix(void) {
    // Ensure the width is a power of 2
    assert(((WIDTH - 1) & WIDTH) == 0);
    int* result = malloc(WIDTH * WIDTH * sizeof(int));
    for (size_t y = 0; y < WIDTH; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            result[IDX(x, y)] = rand();
        }
    }
    return result;
}

int main(void) {
    // Construct the matrices
    int* a = generate_random_matrix();
    int* b = generate_random_matrix();
    int* result = calloc(WIDTH * WIDTH, sizeof(int));
	
	// creates as many threads as needed
    pthread_t thread_ids[NTHREADS];
    struct worker_args thread_args[NTHREADS];
    // Create threads with given worker function and argument
    for (size_t i = 0; i < NTHREADS; i++) {
		// gives all of the workers both arrays
        thread_args[i].a = a;
        thread_args[i].b = b;

		// gives the resulting array all of the threads are outputting into
        thread_args[i].result = result;
        thread_args[i].id = i;

		// creates each of the threads to start doing matrix multiplication
        // if (pthread_create(thread_ids + i, NULL, multiply_worker, thread_args + i) != 0) {
        if (pthread_create(thread_ids + i, NULL, multiply_worker, &thread_args[i]) != 0) {
            perror("unable to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (size_t i = 0; i < NTHREADS; i++) {
        if (pthread_join(thread_ids[i], NULL) != 0) {
            perror("unable to join thread");
            return 1;
        }
    }

    // Compute the result
    int* naive = naive_multiply(a, b);
    for (size_t y = 0; y < WIDTH; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            assert(naive[IDX(x, y)] == result[IDX(x, y)]);
        }
    }

    puts("done");
    free(a);
    free(b);
    free(result);
    return 0;
}