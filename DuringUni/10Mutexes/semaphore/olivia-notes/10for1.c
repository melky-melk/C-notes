#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define ATIMES 10
#define BTIMES 1

#define THREADS 110

sem_t a_wait;
sem_t b_wait;

void *a() {
    sem_wait(&a_wait);
    printf("Func A\n");
    sem_post(&b_wait);
}

void *b() {
    sem_wait(&b_wait);
    printf("Func B\n");
    for (int i = 0 ; i < ATIMES ; i++) {
        sem_post(&a_wait);
    }
}

int main() {
    pthread_t threads[THREADS];

    sem_init(&a_wait, 0, 10);
    sem_init(&b_wait, 0, -9);

    for (int i = 0 ; i < THREADS/11 ; i++) {
        for (int q = 0 ; q < 11 ; q++) {
            if (q < 10) {
                pthread_create(&threads[i + q], NULL, a, NULL);
            }
            if (q == 10) {
                pthread_create(&threads[i + q], NULL, b, NULL);
            }
        }
    }

    for (int i = 0 ; i < THREADS/3 ; i++) {
        for (int q = 0 ; q < 3 ; q++) {
            if (q < 2) {
                pthread_join(threads[i + q], NULL);
            }
            if (q == 2) {
                pthread_join(threads[i + q], NULL);
            }
        }
    }

    sem_destroy(&a_wait);
    sem_destroy(&b_wait);

    return 0;
}