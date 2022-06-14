// NOTE: I CURRENTLY HAVEN'T FINISHED THIS QUESTION BUT
// FEEL FREE TO USE THIS AS A SCAFFOLD

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#define MAIN_THREAD_TIMEOUT (60)
#define N_JOBS (200)

// Data structure for storing the thread jobs.
struct thread_job {
    void (*fn) (void*);
    void * data;
};

// Data structure for making a new thread job given a method and
// a pointer to its argument.
struct thread_job* thread_job_new(void(*fn)(void*), void* data) {
    struct thread_job * job = malloc(sizeof(struct thread_job));
    job->fn = fn;
    job->data = data;
    return job;
}

// Each thread needs to access its own mutex and
// the job we want to assign to it. 
struct thread_data {
    pthread_t thread_id;
    pthread_mutex_t lock;
    struct thread_job * job;
};

// When we tell the pool to run some job, the pool figures out which thread
// should get the next job, assigns that task to the thread's memory (thread_data struct)
// then unlocks that mutex, so the thread which was waiting on that mutex will now
// continue performing its code, and it will know which method to call based on 
// the value of job within its thread_data struct. 

// Data structure for our actual pool of threads - array of
// thread data structs, and variable to store our array. 
struct thread_pool {
    struct thread_data * threads;
    int num;
};

void thread_job_destroy(struct thread_job* j);

void* thread_pool_work(void* arg);

// Method to create a new thread pool and launch all of our
// threads. 
struct thread_pool* thread_pool_new(size_t n) {

}

void thread_pool_execute(struct thread_pool* pool, struct thread_job* job);
void thread_pool_destroy(struct thread_pool* pool);

struct work_data
{
    uint32_t time;
    uint32_t work_id;
};

void mysleep(void *arg)
{
    struct work_data *data = (struct work_data *)arg;
    printf("is working on job %u\n", data->work_id);
    fflush(stdout);
    sleep(data->time);
    free(data);
}

int main()
{
    struct thread_pool *pool = thread_pool_new(8);
    for (size_t i = 0; i < N_JOBS; i++)
    {
        struct work_data *d = malloc(sizeof(struct work_data));
        d->time = 1;
        d->work_id = i;
        struct thread_job *job = thread_job_new(mysleep, d);
        thread_pool_execute(pool, job);
    }
    sleep(MAIN_THREAD_TIMEOUT);
    thread_pool_destroy(pool);
    puts("Finishing up now!");
    return 0;
}