// Have one mutex for waiting; all the passengers lock and unlock
// immediately - its like a gate.

// When bus arrives, it locks and DOESNT unlock immediately. this 
// means that any passengers who try to join the waiting passengers 
// cannot, which enables us to achieve the requirement that passengers 
// have to wait for the next bus if they arrive while the bus is being boarded. 

// After obtaining and releasing the waiting mutex, riders attempt to 
// get a spot on the next bus that is going to arrive. This is represented
// by a semaphore that starts at BUS_CAPACITY, and decrements down to 0, and 
// it is a special queue for the riders who WILL have a spot on the next bus. 

// Once the bus arrives, the bus has its own semaphore representing its 
// seats. So that we can wait for everyone on the next ride to get on before the bus leaves,
// we will calculate, based on the special queue mutex (previous paragraph)
// how many riders we will have, from 0 to BUS_CAPACITY. 

// The bus have a mutex with 0 spots. We will now sem_post the number of times 
// as per passengers that are going to get on the bus. This allows those 
// passengers who got into the special queue through sem_wait to now board the bus 
// through sem_wait on the SEATS semaphore. 

// After this semaphore is back to 0, the bus knows all the passengers in the 
// special queue have boarded, so it can now depart. After leaving, we will open 
// back up the 'gate' for waiting, and open up the special queue back to BUS_CAPACITY 
// so that the cycle can continue. 

// when the sem is greater than 0 then it locks and doesnt work

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUS_CAPACITY 15

// Using global variables because i'm a lazy girl.
// Challenge to the reader - move these global variables 
// into a struct that gets passed into the thread functions 
// as part of its void * args. 

pthread_mutex_t gate;
// the starting capacity
sem_t station_capacity;
sem_t avaliable_seats;
static int bus_ride_counter = 0;

void board_bus(int rider_id) {
    // Try and get a seat seats taken starts at 0, once the bus comes the seats increment and the semaphores are able to take them
    sem_wait(&avaliable_seats);

    printf("Rider %d is now boarded\n", rider_id);
}

void * rider(void * arg) {
    // Our arg is our id; we'll wait this time 
    int id = *((int *) arg);
    sleep(id);

    // Now we want to enter the waiting area 
    pthread_mutex_lock(&gate);
    pthread_mutex_unlock(&gate);

    printf("Rider %d is now waiting\n", id);

    // See if we can get in the bus if there are enough seats (decrimenting the seats), meaning check if it is 0 if it is 0 the station is at capacity, and the rider cannot enter the station or attempt to board
    sem_wait(&station_capacity);

    // will block the thread until a seat is avaliable to actually be taken before they can continue the function call
	// the bus will post the sem and allow it to actually board
    sem_wait(&avaliable_seats);

    printf("Rider %d boarded the bus!\n", id);

}

void * bus(void * arg) {

    // Wait a little bit before arriving
    sleep(5);
    printf("Bus is now arriving to the stop.\n");

    // Take the waiting lock, so no other passengers can 
    // board unless they were already waiting 
    pthread_mutex_lock(&gate);

    // Check how many are waiting in the station
    int num;
    sem_getvalue(&station_capacity, &num);
    num = BUS_CAPACITY - num;

    // increment the value so the passengers who are waiting at the semaphore can be let through
    printf("Bus is going to board %d seats for passengers already waiting\n", num);
    for (int i = 0; i < num; i++) sem_post(&avaliable_seats);

    // Wait until they've all boarded
	// meaning keep checking the value until it is 0 again, meaning taht all the passengers havd finished decrimenting
    while (num != 0) {
        sem_getvalue(&avaliable_seats, &num);
    }
    
    printf("All the passengers have boarded, lets go!\n");
    sleep(2);
    bus_ride_counter++;
    printf("Bus ride %d complete.\n", bus_ride_counter);

    // now that the ride has occured, the station capacity an be incremented again and passengers can go to the waiting zone
    sem_getvalue(&station_capacity, &num);
    for (int i = num; i < BUS_CAPACITY; i++) {
        sem_post(&station_capacity);
    }

    // Unlock mutex for passengers to enter waiting area. 
    pthread_mutex_unlock(&gate);
}

int main(int argc, char ** argv) {
    // Initialise the locks.
    pthread_mutex_init(&gate, NULL);

    // Our current queue semaphore starts with 15 current queue spots available, so then once the station reaches its capacity it will block people from getting into the waiting area for the bus
    sem_init(&station_capacity, 0, BUS_CAPACITY);

    // Our seats semaphore starts with no spots taken up on the bus yet (because no one had boarded it yet) and the bus will need to post to allow riders to come on
    sem_init(&avaliable_seats, 0, 0);

    // Make some number of riders, lets say 20
    pthread_t ids[20];
    int nums[20];

    for (int i = 0; i < 20; i++) {
        nums[i] = i;
		// this will start running all of the riders simulteneously
        pthread_create(ids+i, NULL, rider, nums+i);
    }

    // Sleep and then make one bus 
    sleep(7);
    pthread_t bus_id;
	
	for (int i = 0; i < 2; i++){
	    pthread_create(&bus_id, NULL, bus, NULL);

		// Join our bus
		pthread_join(bus_id, NULL);
	}

    // Join up all our rider threads 
    for (int i = 0; i < 20; i++) {
        pthread_join(ids[i], NULL);
    }
}