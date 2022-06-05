#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

// mutexes do the same thing as a global variable that you keep resetting

void* routine(){
	for (int i = 0; i < 1000000; i++){
		// its protecting a piece of code inbetween the mutexted
		// taking a lock, waiting until it is unlocked, locking it when completing an operation 
		pthread_mutex_lock(&mutex);
		// if any point, a thread is executing the code inbetween, there isnt any other thread that can execute this line at the same time
		mails++;
		// and unlocking it when finished
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment mails
		// write back to mails
	}
}

int main(int argc, char** argv){
	pthread_t p1, p2;

	// creating the actual mutex, setting it to NULL is the default
	pthread_mutex_init(&mutex, NULL);

	// creates a thread from the address
	// the next is the attribute you are giving to it
	// next is the function you are performing
	// the last is a void pointer, which the function can unpack to get all the information you need
	if (pthread_create(&p1, NULL, &routine, NULL) != 0){
		return 1;
	}

	if (pthread_create(&p2, NULL, &routine, NULL) != 0){
		return 2;
	}

	if (pthread_join(p1, NULL) != 0){
		return 3;
	}

	if (pthread_join(p2, NULL) != 0){
		return 4;
	}

	// freeing the memory allocated
	pthread_mutex_destroy(&mutex);
	printf("number of mails %d\n", mails);

	return 0;
}