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
	pthread_t threads[4];
	// creating the actual mutex, setting it to NULL is the default
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++){
		
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0){
			perror("Failed to create thread");
			return 1;
		}
		printf("thread %d has started\n", i);

		// when you create the thread, you immediately run it, so its essentually just running the function
		// if you join the threads in the loop it is not simultenious, because they all have to finish execution before the next increment happens
		// only 1 thread running at once, which defeats the purpose of parrallelism
	}
	
	// so when they are created, all of them start running

	// when they are 
	for (int i = 0; i < 4; i++){
		// waiting for the thread to finish?
		if (pthread_join(&threads[i], NULL) != 0)
			return 2;
		printf("thread %d has finished\n", i);
	}

	// freeing the memory allocated
	pthread_mutex_destroy(&mutex);
	printf("number of mails %d\n", mails);

	return 0;
}