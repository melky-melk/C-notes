#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

void* roll_dice(){
	// cant return a local value inside a function because those values will be deallocated in the stack later after it is finished
	// so you need to allocate memory in the heap
	int value = (rand() % 6) + 1;
	int* result = malloc(sizeof(int));
	*result = value;
	return (void* ) result;
	// can call pthread_exit isntead of return
	// pthread_exit((void*) result)
}

int main(int argc, char** argv){
	int* res;

	srand(time(NULL));
	pthread_t th;

	// the start routine for the thread must be a double pointer
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0){
		return 1;
	}

	// so it takes a reference to a pointer, double pointer. so it sets the value of the double pointer to the result 
	// it would be cast back into the result pointer
	if (pthread_join(th, (void**) &res) != 0){
		return 2;
	}

	printf("Result: %d\n", *res);

	// because it is allocated in the thread you need to deallocate it here
	free(res);
	return 0;
}
// can use pthread_exit(0) to stop one of the threads but not the rest of them