#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#define MAX 3

sem_t boarding_seats;
pthread_mutex_t station;

// any variables you need
void * passenger(void * arg){
	int counter = *((int *)arg);
	puts("Passenger: I am trying to enter the station.");
	// if some otehrs are boarding then you pause it here
	pthread_mutex_unlock(&station);

	// checks if the lock is in use (i.e. if its locked by something else), if it is then it prints a message and locks
	if (/* pthread_mutex_trylock(&station) != 0 || */ counter > 3){
		// once its unlocked you can pass through
		puts("Passenger: Station is full. Waiting for the next round.");
		// then locks until its avaliable
		pthread_mutex_lock(&station);
	}

	pthread_mutex_unlock(&station);

	puts("Passenger: In station now, waiting for the next bus.");
	// starts at 0, then once the bus arrives it incriments and lets things through
	sem_wait(&boarding_seats);

	int passengers_remaining;
	sem_getvalue(&boarding_seats, &passengers_remaining);
	
	printf("Passenger: %d boarding. There are %d left.\n", counter, passengers_remaining);
	return NULL;
}

void * bus(void * arg){
	puts("Bus: BUS ARRIVING");

	int passengers_waiting;
	pthread_mutex_lock(&station);
	sem_getvalue(&boarding_seats, &passengers_waiting);

	if (passengers_waiting == 0){
		puts("Bus: No passengers. Depart!");
		return;
	}

	printf("Bus: %d passengers are waiting. Board!\n", passengers_waiting);

	if (passengers_waiting > MAX){
		passengers_waiting = MAX;
	}

	for (int i = 0; i < passengers_waiting; i++){
		// will let the passengers through
		sem_post(&boarding_seats);
	}   

	puts("Bus: All passengers have boarded. Depart!");
	pthread_mutex_unlock(&station);

	*counter = passengers_waiting;

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
			// pthread_create(passenger_threads + (counter), NULL, passenger, NULL);
			counter++;

			// if (counter == MAX){
			// 	pthread_mutex_lock(&station);
			// }
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