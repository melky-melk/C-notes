#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define THREAD_NUM 16

sem_t semaphore;
// semaphores are either decrimented or incremented, when it is 0, it will allow a thread to process


void* routine(void* args){
	// wait is similar to a lock, post is similar to an unlock
	// going to check the semaohre value, if it is 0, then it will wait on the semaphore, if it is higher then it will decriment it
	printf("(%d) Waiting in the login queue\n", * (int*)args);
	sem_wait(&semaphore);
	printf("(%d) Logged in\n", * (int*)args);
	sleep(rand() % 5 + 1);
	printf("(%d) Logged out\n", * (int*)args);
	// it increments the value of the semaphore so more threads can get in
	sem_post(&semaphore);
	free(args);
}

int main(int argc, char** argv){
	pthread_t threads[THREAD_NUM];
	// if you have multiple processes with multiple threads pass in 1 instead of 0

	// the number at the end is the amount of threads that are able to run simultenously
	sem_init(&semaphore, 0, 12);

	// threads being the number of users
	for (int i = 0; i < THREAD_NUM; i++){
		int* a = malloc(sizeof(int));
		*a = i;

		pthread_create(&threads[i], NULL, &routine, a);
	}

	for (int i = 0; i < THREAD_NUM; i++){
		pthread_join(threads[i], NULL);
	}

	sem_destroy(&semaphore);
	return 0;
}