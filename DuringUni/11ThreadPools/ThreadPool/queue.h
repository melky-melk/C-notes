#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct queue
{
    int head;
    int capacity;
    int count;
    void** array;
} queue_t;

queue_t* queue_init(int capacity);

void queue_destroy(queue_t* queue);

void queue_push(queue_t* queue, void* element);

void* queue_pop(queue_t* queue);

void queue_print(queue_t* queue, void (*print_item)(void* item));

#endif