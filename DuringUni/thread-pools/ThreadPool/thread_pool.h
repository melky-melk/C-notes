#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "queue.h"
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

typedef struct thread_pool
{
    queue_t* task_queue;
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_cond;

    int num_threads;
    pthread_t* threads;
} thread_pool_t;

typedef struct thread_task
{
    void* arg;
    void* (*func)(void* arg);
    void* result;
    sem_t* sync;
} thread_task_t;

thread_pool_t* thread_pool_init(int num_threads);

void thread_pool_destroy(thread_pool_t* thread_pool);

thread_task_t* create_task(thread_pool_t* thread_pool, void* arg, void* (*func)(void* arg), bool synchronsiable);

void* get_task_result(thread_task_t* task);

#endif