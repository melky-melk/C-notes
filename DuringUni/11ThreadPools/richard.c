#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>


#define MAIN_THREAD_TIMEOUT (40)
#define N_JOBS (200)

//threadpool.

//modified tut sheet repsonse, instead of implementing the asked for thread pool.
//implemented a dumb thread pool that will instantly start any job queued,
//and using mutecies will assign a new job to any free thread.

//asked for threadpool requires an ID for each thread, 
//and a threadpool controller thread (or at least an integer which states the last thread to select a job) which assigns the jobs in a round robin fashion.


//semaphore needed to ensure that threads block if no jobs available.
sem_t jobs[1];
//mutex needed to lock queue so that we don't get race conditions
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//struct for each job for each thread to run.
typedef struct thread_job{
    void* arg;
    void (*jf)(void*);
    struct thread_job* next;
} thread_job;


//thread_pool struct, containing all my jobs and threads, and if my pool is active
typedef struct thread_pool{
    //FIFO queue/linked list.
    thread_job* job_list;
    pthread_t* threads;
    int num_threads;
    //is my pool active, ie. currently running
    int active;
} thread_pool;

//function that each thread runs, will block until job, and then run the job.
void* thread_func(void* arg){
    thread_pool* pool = (thread_pool*) arg;
    printf("Started thread!\n");
    while(pool->active){
        //when a job is activated this semaphore is incremented, here we wait until a job is posted.
        sem_wait(jobs);
        if (!pool->active){
            //alternatively our threadpool increments our semaphore when we want to close the pool.
            printf("Closing threads!\n");
            return NULL;
        }
        //lock our queue mutex, as we are accessing our queue.
        pthread_mutex_lock(&lock);
        //select a job from the top of the list.
        thread_job* job = pool->job_list;
        pool->job_list = job->next;
        pthread_mutex_unlock(&lock);

        //run job here
        (*job->jf)(job->arg);
        free(job);
    }
    printf("Closing threads!\n");
    return NULL;
}

//construct a new thread_job struct. 
struct thread_job* thread_job_new(void(*fn)(void*), void* data){
    thread_job* out = calloc(1, sizeof(thread_job));
    out->arg = data;
    out->jf = fn;
    return out;
}


//construct a new thread_pool
thread_pool* thread_pool_new(size_t n){
    thread_pool* pool = calloc(1, sizeof(thread_pool));
    pool->threads = calloc(n, sizeof(pthread_t));
    pool->num_threads = n;
    pool->active = 1;
    //initialise our semaphore
    sem_init(jobs, 0, 0);
    for (int i = 0; i < n; i++){
    	//create our threads
        pthread_create(pool->threads + i, NULL, thread_func, pool);
    }
    printf("Finished creating therads!\n");
    return pool;
}

//append a thread_job to our thread_pool
void thread_pool_execute(struct thread_pool* pool,
    struct thread_job* job){
    //lock our queue mutex.
    pthread_mutex_lock(&lock);
    thread_job* current = pool->job_list;
    //if we don't have a job in our list, we cannot append it to our job->next.
    if (!current){
    	//adds the job to the front of our list.
        pool->job_list = job;
        //increment our semaphore 
        sem_post(jobs);
        //unlock our mutex.
        pthread_mutex_unlock(&lock);
        return;
    }
    while(current->next){
    	//traverses to the back of our job_list.
        current = current->next;
    }
    //adds our job to the back of our list.
    current->next = job;
    //increments our semaphore
    sem_post(jobs);
    pthread_mutex_unlock(&lock);
}


//destroy our threadpools, can cause "memory leaks" if called early.
void thread_pool_destroy(struct thread_pool* pool){
    //this "can" cause race conditions, if we alter our code.
    pool->active = 0;
    for (int i = 0; i < pool->num_threads; i++){
    	//frees any locked jobless threads.
        sem_post(jobs);
    }
    for(int i = 0; i < pool->num_threads; i++){
        pthread_join(pool->threads[i], NULL);
    }
    free(pool->threads);
    free(pool);
}

//rest has been provided through the tutorial sheet 

struct work_data {
    uint32_t time;
    uint32_t work_id;
};

void mysleep(void* arg) {
    struct work_data* data = (struct work_data*) arg;
    printf("is working on job %u\n", data->work_id);
    fflush(stdout);
    sleep(data->time);
    free(data);
}

int main() {
    struct thread_pool* pool = thread_pool_new(8);
    for(size_t i = 0; i < N_JOBS; i++) {
        struct work_data* d = malloc(sizeof(struct work_data));
        d->time = 1;
        d->work_id = i;
        struct thread_job* job = thread_job_new(mysleep, d);
        thread_pool_execute(pool, job);
    }
    sleep(MAIN_THREAD_TIMEOUT);
    thread_pool_destroy(pool);
    puts("Finishing up now!");
return 0;
}
