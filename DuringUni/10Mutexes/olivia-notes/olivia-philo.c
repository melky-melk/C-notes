#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define THINKERS 5

static pthread_mutex_t chopsticks[THINKERS];

void* dine(void* arg) {
    const unsigned id = *((unsigned *)arg);

    while (true) {
        //get chopsticks
        if (id < THINKERS - 1) {
            pthread_mutex_lock(&chopsticks[id]);
            pthread_mutex_lock(&chopsticks[id+1]);
        } else {
            //IMPORTANT
            //the final philosopher must grab his chopsticks the opposite way to
            //prevent a deadlock.
            pthread_mutex_lock(&chopsticks[0]);
            pthread_mutex_lock(&chopsticks[id]);
        }
        printf("The philosopher %u is eating.\n", id);
        if (id < THINKERS - 1) {
            pthread_mutex_unlock(&chopsticks[id]);
            pthread_mutex_unlock(&chopsticks[id+1]);
        } else {
            //IMPORTANT
            //the final philosopher must grab his chopsticks the opposite way to
            //prevent a deadlock.
            pthread_mutex_unlock(&chopsticks[0]);
            pthread_mutex_unlock(&chopsticks[id]);
        }
        printf("The philosopher %u is thinking.\n", id);

        //sleep to give time for next philosopher to eat and this one to think
        sleep(1);

    }
    return NULL;
}

int main(void) {
    unsigned args[THINKERS];
    pthread_t thinkers[THINKERS];

    //create chopsticks
    for (size_t i = 0 ; i < THINKERS ; i++) {
        if (pthread_mutex_init(chopsticks + i, NULL) != 0) {
            perror("unable to initialise mutex");
            return 1;
        }
    }

    //launch threads
    for (size_t i = 0 ; i < THINKERS ; i++) {
        args[i] = i;
        if (pthread_create(thinkers + i, NULL, dine, args + i) != 0) {
            perror("unable to create thread");
            return 2;
        }
    }

    //join threads
    for (size_t i = 0 ; i < THINKERS ; i++) {
        if (pthread_join(*thinkers + i, NULL) != 0) {
            perror("unable to join thread");
            return 3;
        }
    }

    //destroy chopsticks
    for (size_t i = 0 ; i < THINKERS ; i++) {
        if (pthread_mutex_destroy(chopsticks + i) != 0) {
            perror("unable to destroy mutex");
            return 4;
        }
    }

    return 0;
}
