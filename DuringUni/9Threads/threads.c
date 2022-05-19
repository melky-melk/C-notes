#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* routine(){
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
}

// compile with -pthread when you compile
// gcc -pthread threads.c -o threads
int main(int argc, char** argv){
	// have to define a place where the apui can store some information about the thread
	pthread_t t1, t2;

	// pointer to thread can put null for default attributes, function pointer to what the threads will do
	// the arguments that will be passed to the function
	// these occur at the exact same time
	if (pthread_create(&t1, NULL, &routine, NULL) != 0 || pthread_create(&t2, NULL, &routine, NULL)){
		return 1;
	}

	// have to wait for the thread to finish execution wait but for threads
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}