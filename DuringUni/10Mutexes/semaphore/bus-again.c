#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAX 3

sem_t boarding_seats;
pthread_mutex_t station;
pthread_cond_t cond_seats;
int total_passengers = 0;

// any variables you need
void * passenger(void * arg){
	int id = *((int*)arg);
	puts("Passenger: I am trying to enter the station.");

	// checks if the lock is in use (i.e. if its locked by something else), if it is then it prints a message and locks
	if (total_passengers > 3 /*|| pthread_mutex_trylock(&station) != 0*/){
		// once its unlocked you can pass through
		puts("Passenger: Station is full. Waiting for the next round.");
		
		while (total_passengers > 3){
			pthread_cond_wait(&cond_seats, &station);
		}
		// then locks until its avaliable
		pthread_mutex_unlock(&station);
	}
	puts("Passenger: In station now, waiting for the next bus.");

	// starts at 0, then once the bus arrives it incriments and lets things through
	sem_wait(&boarding_seats);

	int passengers_remaining;
	sem_getvalue(&boarding_seats, &passengers_remaining);
	
	pthread_mutex_lock(&station);
	printf("Passenger: %d boarding. There are %d left in the station.\n", id, passengers_remaining);
	pthread_mutex_unlock(&station);
	return NULL;
}

void * bus(void * arg){
	puts("Bus: BUS ARRIVING");

	if ((total_passengers) == 0){
		puts("Bus: No passengers. Depart!");
		return NULL;
	}

	printf("Bus: %d passengers are waiting. Board!\n", total_passengers);

	int boarding_passengers = total_passengers;
	if (total_passengers > MAX){
		boarding_passengers = MAX;
	}

	for (int i = 0; i < boarding_passengers; i++){
		// will let the passengers through
		sem_post(&boarding_seats);
	}  

	pthread_mutex_lock(&station); 
	printf("Bus: All %d passengers have boarded. Depart!\n", boarding_passengers);
	total_passengers -= boarding_passengers;
	pthread_mutex_unlock(&station);
	pthread_cond_signal(&cond_seats);

	return NULL;
}

int main() {
	char buffer[6];
	pthread_t bus_thread;
	pthread_t passenger_threads[100];
	int counter = 0;

	sem_init(&boarding_seats, 0, 0);
	pthread_mutex_init(&station, NULL);

	while(fgets(buffer, 6, stdin)){
		if(!strncmp(buffer, "BUS", 3)){
			pthread_create(&bus_thread, NULL, bus, (void*) &counter);
			// pthread_create(&bus_thread, NULL, bus, NULL);
		}
		
		else if(!strncmp(buffer, "PASS", 4)){
			pthread_create(passenger_threads + (counter), NULL, passenger, (void*) &counter);
			total_passengers++;
			counter++;
		}
		
		else if(!strncmp(buffer, "QUIT", 4)){
			exit(0);
		}
		
		else{
			printf("Unknown command\n");
		}
	}
	
	pthread_join(bus_thread, NULL);
	for(int i = 0; i < counter; i++){
		pthread_join(passenger_threads[i], NULL);
	}

	pthread_mutex_destroy(&station);
	sem_destroy(&boarding_seats);
    return 0;
}