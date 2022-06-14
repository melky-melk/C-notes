#include "thread_pool.h"
#include "queue.h"
#include <stdio.h>

void* print_from(void* arg){
    int start = *((int*)arg);

    for (int i = 0; i < 100; i++)
        printf("%d\n", i + start);

    return NULL;
}

void* add_thousand(void* arg){
    int* x = malloc(sizeof(int));
    *x = *((int*)arg) + 1000;
    return x;
}

void thread_pool_test(){
    thread_pool_t* thread_pool = thread_pool_init(5);

    int a = 1;
    create_task(thread_pool, &a, print_from, false);

    int b = 100;
    create_task(thread_pool, &b, print_from, false);

    int c = 1000;
    thread_task_t* task = create_task(thread_pool, &c, add_thousand, true);

    thread_pool_destroy(thread_pool);
    int* x = get_task_result(task);
    printf("%d\n", *x);
    free(x);
}

void dummy(void* x){
    printf("%d", *((int*)x));
}

void basic_queue_test()
{
    queue_t* queue = queue_init(2);

    queue_print(queue, dummy);

    int a = 3;
    int b = 6;
    int c = 4;

    queue_push(queue, &a);
    queue_push(queue, &b);
    queue_push(queue, &c);

    queue_print(queue, dummy);

    queue_pop(queue);
    queue_pop(queue);

    queue_print(queue, dummy);

    queue_push(queue, &a);

    queue_print(queue, dummy);

    int* x = queue_pop(queue);
    printf("%d\n", *x);

    queue_print(queue, dummy);

    queue_destroy(queue);
}

int main()
{
    // basic_queue_test();
    thread_pool_test();

    return 0;
}