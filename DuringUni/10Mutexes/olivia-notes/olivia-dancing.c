#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NWHITE 9
#define NRED (NWHITE * 2)

static sem_t max_r;
static sem_t max_w;

void red(void) {
    printf("dancing in red\n");
}
void white(void) {
    printf("dancing in white\n");
}

void* red_thread(void* args) {
    sem_wait(&max_r);

    red();
    return NULL;
}

void* white_thread(void* args) {
	// will first wait if there is an opening
	// if there is 1 white dancer spot avaiable then take it and continue 
    sem_wait(&max_w);

    white();
    sem_post(&max_r);
    sem_post(&max_r);
    sem_post(&max_w);
    return NULL;
}

int main() {
    pthread_t ids[NWHITE + NRED];

    sem_init(&max_r, 0, 2);
    sem_init(&max_w, 0, 1);

    for (int i = 0 ; i < NWHITE; i++) {
        for (int q = 0 ; q < 2 ; q++) {
            pthread_create(ids + i * 3 + q, NULL, red_thread, NULL);
        }
        pthread_create(ids + i * 3 + 2, NULL, white_thread, NULL);
    }

    sem_destroy(&max_r);
    sem_destroy(&max_w);

    return 0;
}
