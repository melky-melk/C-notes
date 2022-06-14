#include "thread_pool.h"

static void* thread_loop(void* arg);

/*
a thread pool essentially just a data structure that takes in a number of threads and launch them all at once
all those inner threads then lock at a semaphore, and the semaphore increments when a task is created and added to the queue
the task will contain a function that will be performed once the semaphore is unlocked
*/

// a contructor to create the threadpool
thread_pool_t* thread_pool_init(int num_threads){
    thread_pool_t* thread_pool = malloc(sizeof(thread_pool_t));

    pthread_mutex_init(&thread_pool->queue_lock, NULL);
    pthread_cond_init(&thread_pool->queue_cond, NULL);

    thread_pool->num_threads = num_threads;
    thread_pool->task_queue = queue_init(num_threads * 2);
    thread_pool->threads = malloc(sizeof(pthread_t) * num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(thread_pool->threads + i, NULL, thread_loop, thread_pool);
    }

    return thread_pool;
}

void thread_pool_destroy(thread_pool_t* thread_pool){
    if (thread_pool == NULL)
        return;

    // Tell threads to end
    for (int i = 0; i < thread_pool->num_threads; i++){
        create_task(thread_pool, NULL, NULL, false);
    }

    // Join on the threads
    for (int i = 0; i < thread_pool->num_threads; i++){
        pthread_join(thread_pool->threads[i], NULL);
    }
    free(thread_pool->threads);
    
    queue_destroy(thread_pool->task_queue);
    pthread_mutex_destroy(&thread_pool->queue_lock);
    free(thread_pool);
}

// gives the functions and arguments the threads inside the threadpool 
thread_task_t* create_task(thread_pool_t* thread_pool, void* arg, void* (*func)(void* arg), bool synchronsiable){
    if (thread_pool == NULL)
        return NULL;

    thread_task_t* task = malloc(sizeof(thread_task_t));

    task->arg = arg;
    task->func = func;
    task->sync = NULL; 

	// gives a semaphore if it wants to be syncronised
    if (synchronsiable){
        task->sync = malloc(sizeof(sem_t));
        sem_init(task->sync, 0, 0);
    }

	// locks the threadpool while adding the new lock so there isnt any race conditions that overwrite
    pthread_mutex_lock(&thread_pool->queue_lock);
	// if the queue is at its capacity then wait on the queue until the queue has more capacity
    if (thread_pool->task_queue->count == thread_pool->task_queue->capacity)
        pthread_cond_wait(&thread_pool->queue_cond, &thread_pool->queue_lock);

	// you can add the thread to the queue because there is capacity 
    queue_push(thread_pool->task_queue, task);

	// then tell all of the other threads that the queue has been updated
	pthread_cond_broadcast(&thread_pool->queue_cond);
    pthread_mutex_unlock(&thread_pool->queue_lock);

	// then you return the thread
    if (synchronsiable)
        return task;
    else
        return NULL;
}

void* get_task_result(thread_task_t* task){
    if (task == NULL)
        return NULL;

    sem_wait(task->sync);
    void* result = task->result;

    sem_destroy(task->sync);
    free(task->sync);
    free(task);

    return result;
}

static void* thread_loop(void* arg){
	thread_pool_t* thread_pool = (thread_pool_t*)arg; 

    bool continue_waiting = true;
	// will enter the main loop where
    while (continue_waiting) {
		// locks while work is being done on the queue
        pthread_mutex_lock(&thread_pool->queue_lock);

		// if the queue is empty then wait until it works again
        if (thread_pool->task_queue->count == 0)
            pthread_cond_wait(&thread_pool->queue_cond, &thread_pool->queue_lock);

		//gets the most recent task added
        thread_task_t* task = queue_pop(thread_pool->task_queue);

		//tells everyone that the task has been popped and a task can start working
        pthread_cond_broadcast(&thread_pool->queue_cond);
        pthread_mutex_unlock(&thread_pool->queue_lock);

        //if the task is not empty then run it, using the argument given
        if (task->func != NULL)
            task->result = task->func(task->arg);
        else
            continue_waiting = false; //otherwise exit the loop

        // If theres no sync, we cleanup the task
        if (task->sync == NULL)
            free(task);
        else
            sem_post(task->sync);
    }

    return NULL;
}