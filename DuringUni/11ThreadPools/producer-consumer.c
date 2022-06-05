/* IN THEORY

PRODUCERS CREATE DATA, WHICH EXISTS IN A SPACE

CONSUMERS USE THAT DATA AND PERFORM ACTIONS ON IT

this is shared memory, one puts things in, the other takes things out
producer amd consumer method relies on having boundaries/a bounded buffer having a limit on how many things can be in a buffer at once


if there are more items in the consumer check for, checking if the buffer is full
checking if the buffer is empty
*/

#include<stdio.h>
#include<pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 2

int buffer[10];
int count = 0;
pthread_mutex_t mutex_buffer;

// can use semaphores because they have values stored in it
sem_t sem_empty;
sem_t sem_full;

void* producer(void* args){
	while (1){
		// produce
		int x = rand() % 100;

		// checks if there are avaliable slots for the semaphore to be added
		sem_wait(&sem_empty);
		pthread_mutex_lock(&mutex_buffer);
		// add to the buffer
		buffer[count] = x;
		count++;
		pthread_mutex_unlock(&mutex_buffer);
		// increment the number of slots taken
		sem_post(&sem_full);
	}
}

void* consumer(void* args){
	while (1){
		//wait until there is at least, 1 value inside the semaphore/1 value inside the buffer, before attempting to take something out
		sem_wait(&sem_full);
		pthread_mutex_lock(&mutex_buffer);

		// Remove from the buffer
		int x = buffer[count - 1];
		count--;

		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&sem_empty);
		// consume
		printf("Got %d\n", x);
	}
}
int main(int argc, char** argv){
	pthread_t thread[THREAD_NUM];
	pthread_mutex_init(&mutex_buffer, NULL);

	// number of avaliable slots in the beginning (the buffer is 10 so 10 empty slots in the beginning)
	sem_init(&sem_empty, 0, 10);
	sem_init(&sem_full, 0, 0);

	for (int i = 0; i < THREAD_NUM; i++) {
		if (i % 2 == 0){
			pthread_create(&thread[i], NULL, &producer, NULL);
		}
		else {
			pthread_create(&thread[i], NULL, &consumer, NULL);
		}

	}
	pthread_mutex_destroy(&mutex_buffer);
	sem_destroy(&sem_empty);
	sem_destroy(&sem_full);
	return 0;
}