/*
In following program uses threads to simulate dancers in a ballroom. Each thread is represents a
person in the ballroom wearing a coloured dress. In the ballroom there is a main stage. However,
dancers are only allowed onto the main stage if they are in a group of three. The second requirement
to entering the main stage is that two of the dancers must be wearing a red dress and the other dancer
must be wearing a white dress.

In the following program, each thread calls the function that corresponds to its colour after it spawns.
i.e. a thread with a red dress calls the red function, a thread with a white dress calls the white 
function.

Your task is to add synchronisation code to red and white such that they block until all three can
enter the main stage together, then the function should return. Suppose two red threads are blocked
on red, and then a white thread calls white, the third thread should wake up the other two threads
and they should all return.

TAKEAWAYS
- only 3 allowed at the same time, has to be in a group of three
- 2 must be red 1 must be white

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define NWHITE 1000
#define NRED (NWHITE * 2)

sem_t red_sem;
sem_t white_sem;
pthread_barrier_t stage;

void red(void)  {puts("red");}
void white(void){puts("white");}

void* red_thread(void *args){
	// going to check the semaohre value, if it is 0, then it will wait on the semaphore, if it is higher then it will decriment it and continue
	// meaning because it starts at 2, it will decriment once (for each thread made) and continue 
	sem_wait(&red_sem);

	//then wait til 3 total dancers on the stage the barrier is like a semaphore that waits when it is greater than 0, but will continue when it is 0
	// it also decriments like a semaphore
	pthread_barrier_wait(&stage);

	red();

	// then increases it again after so more dancers can take the stacge
	sem_post(&red_sem);
	return NULL;
}
void* white_thread(void *args){
	// will first wait if there is an opening
	// if there is 1 white dancer spot avaiable then take it and continue if not wait until there is a spot availiable
	sem_wait(&white_sem);

	pthread_barrier_wait(&stage);
	white();

	sem_post(&white_sem);
	return NULL;
}

int main(void){
	sem_init(&white_sem, 0, 1);
	sem_init(&red_sem, 0, 2);
	pthread_barrier_init(&stage, NULL, 3);

	pthread_t ids[NWHITE + NRED];

	for (size_t i = 0; i < NWHITE; ++i) {
		pthread_create(ids + i * 3 + 0, NULL, red, NULL);
		pthread_create(ids + i * 3 + 1, NULL, red, NULL);
		pthread_create(ids + i * 3 + 2, NULL, white, NULL);
	}

	for (size_t i = 0; i < NWHITE + NRED; i++){
		pthread_join(ids[i], NULL);
	}
}
