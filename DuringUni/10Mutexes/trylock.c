#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;

void* routine(void* arg){
	// try locks, tries to lock the mutex, but it doesnt always get it, if you dont get it, then that means you shouldnt execute the code
	//if it is 0 that means you got it

	//try lock instantly attempts to get the lock
	// whereas the regular lock WAITS until the lock has been avaliable
	if (pthread_mutex_trylock(&mutex) == 0){
		// within the lcok it does something time consuming and it keeps waiting
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	//otherwise if it cannot get it that means it is busy 
	else {
		puts("didnt get lock");
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
	}
	
	// when they are 
	for (int i = 0; i < 4; i++){
		// waiting for the thread to finish? and returning the value?
		if (pthread_join(threads[i], NULL) != 0)
			return 2;
	}
}