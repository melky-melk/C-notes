#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define PASSENGERS 100

//semaphore objects to control flow of the program.
sem_t boarding;
//added this one because sometimes the bus was printing that it departed early.
sem_t depart;

void* boardBus(void* arg) {
    printf("Passenger %d, waiting.\n", *(int*)arg);
    //Passengers always wait for the passenger in front of them to finish
    //boarding. However it is the bus that defines this not the passenger.
    sem_wait(&boarding);
    //On the other hand the passengers define when they have all got on the bus.
    //They will increment the semephore for the bus to to depart.
    sem_post(&depart);
    printf("Passenger %d has boarded.\n", *(int*)arg);

    return NULL;
}

void bus_pickup(int passengers, int *travelled) {
    //This is just calculating the num of passengers for this trip.
    printf("\nThe bus has arrived\n%d passengers waiting.\n",
                passengers - *(int*)travelled);
 
    // gets the passengers that currently want to board
	int temp =  passengers - *travelled;
    if (temp > 30) {
        temp = 30;
    }
    printf("Picking up %d passengers.\n", temp);
    
	for (int i = 0; i < temp ; i++) {
        //This loop will increment the sempahore to let all the passengers on
        //that the bus can fit and whom were waiting for the bus.
        sem_post(&boarding);
        //We also decrement the sempahore that lets the bus know when it can
        //depart. Which is once all the passengers have finished boarding.
        sem_wait(&depart);
    }

	//then adds the number of passengers it let through
    *travelled = *travelled + temp;
    //Since we initialised the sem at 0 we have to do an extra post to hit 1
    sem_post(&depart);
    //Then we have the final check, this will only allow flow when the passengers
    //who were elegible to board have finished.
    sem_wait(&depart);
    printf("Bus departing.\n\n");
}

int main() {
    pthread_t passenger_threads[PASSENGERS];
    //Sems initialised at 0 so no boarding or departing can happen until
    //events that allow it have incremented them.
    sem_init(&boarding, 0, 0);
    sem_init(&depart, 0, 0);
    unsigned int seed = time(NULL);

    //int num_passengers;
    int travelled = 0;
    int id[PASSENGERS];
    int rand_mod = 0;


    for (int i = 0 ; i < PASSENGERS ; i++) {
        id[i] = i;
        rand_mod++;
        pthread_create(&passenger_threads[i], NULL, boardBus, &id[i]);
		// so the bus comes at random times and takes the number of passengers
        if (rand_mod + rand_r(&seed) % 20 > 75) {
            bus_pickup(id[i] + 1 , &travelled);
            sleep(1);
            rand_mod = 0;
        }
    }

    while(travelled < PASSENGERS) {
        bus_pickup(PASSENGERS, &travelled);
    }

    for (int i = 0 ; i < PASSENGERS ; i++) {
        pthread_join(passenger_threads[i], NULL);
    }

    sem_destroy(&boarding);

    return 0;
}
