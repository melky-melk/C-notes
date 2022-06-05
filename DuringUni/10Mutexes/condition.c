#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

int fuel = 0;
pthread_mutex_t fuel_mutex;
pthread_cond_t cond_fuel;

void* fuel_filling(void* arg){
	for (int i = 0; i < 5; i++){
		pthread_mutex_lock(&fuel_mutex);
		fuel += 15;
		printf("filling fuel %d\n", fuel);
		pthread_mutex_unlock(&fuel_mutex);
		// once it has filled it a little, it will send a signal knowing
		pthread_cond_signal(&cond_fuel);
		sleep(1);
	}
}

void* car(void* arg){
	// when the fuel mutex is locked, that means that nothing else can unlock 
	pthread_mutex_lock(&fuel_mutex);

	// the condition itself isnt in the condwait variable, its contained in the while loop statement
	while (fuel < 40){
		puts("no fuel waiting");
		// waits for a signal from another thread, which may or may not change the condition
		// this doesnt know the variable of fuel, but instead just pauses this trhead, and unlocks the actual mutex to see if the condition ever changes
		// it waits for a signal to be sent by another thread
		pthread_cond_wait(&cond_fuel, &fuel_mutex);
		// checks again for the condition

		// pthread_cond_wait is the same thing as
		/*
		pthread_mutex_unlock(&mutex_fuel);
		wait for signal on cond fuel
		pthread_mutex_lock(&mutex_fuel);
		*/
	}

	// condition variables are variables that can be checked
	// want to only take fuelif there is some avaliable
	fuel -= 40;
	printf("got fuel now left: %d\n", fuel);
	pthread_mutex_unlock(&fuel_mutex);
}

int main(int argc, char** argv){
	pthread_t threads[2];
	pthread_mutex_init(&fuel_mutex, NULL);
	pthread_cond_init(&cond_fuel, NULL);

	void* functions[2] = {car, fuel_filling};

	for (int i = 0; i < 2; i++){
		pthread_create(&threads[i], NULL, functions[i], NULL);
	}

	for (int i = 0; i < 2; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&fuel_mutex);
	pthread_cond_destroy(&cond_fuel);
}