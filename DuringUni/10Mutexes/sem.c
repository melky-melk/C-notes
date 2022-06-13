#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t a_sem;
sem_t b_sem;

void* a(void* arg){
	// because it is not 0, it passes
	sem_wait(b_sem);
	puts("a has fired");
	// 
	sem_post(b_sem);
}

void* b(void* arg){
	sem_wait(b_sem);
	puts("b has fired");
}

int main(){
	sem_init(a_sem, 0 , 0);
	sem_init(b_sem, 0 , -9);
}