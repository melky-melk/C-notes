#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg){
	int index = * (int*)arg;
	printf("%d ", primes[index]);
}

// passing unique values into each thread, better for parallelism, when they run and dont depend on each other
int main(int argc, char** argv){
	pthread_t threads[10];

	for (int i = 0; i < 10; i++){
		// you cannot simply give the thread i, because it is possible that the address for i will change in the meantime
		// it might read in the value for 0, then while it is processing, the value of i increments to 1 and will thus print the wrong thing
		int* a = malloc(sizeof(int));
		*a = i;

		if (pthread_create(&threads[i], NULL, &routine, a) != 0){
			perror("Failed to create thread");
			return 1;
		}

		free(a);
	}

	for (int i = 0; i < 10; i++){
		if (pthread_join(&threads[i], NULL) != 0){
			perror("Failed to join thread");
			return 1;
		}
	}

	return 0;
}