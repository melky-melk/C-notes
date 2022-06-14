#include "queue.h"

static int get_index(queue_t* queue, int i);

queue_t* queue_init(int capacity)
{
    queue_t* queue = malloc(sizeof(queue_t));

    queue->array = malloc(capacity * sizeof(void*));
    queue->count = 0;
    queue->head = 0;
    queue->capacity = capacity;

    return queue;
}

void queue_destroy(queue_t* queue)
{
    if (queue == NULL)
        return;

    free(queue->array);
    free(queue);
}

void queue_push(queue_t* queue, void* element)
{
    if (queue == NULL || queue->capacity == queue->count)
        return;

    queue->array[get_index(queue, queue->count)] = element;
    queue->count++;
}

void* queue_pop(queue_t* queue)
{
    if (queue == NULL || queue->count == 0)
        return NULL;
    
    void* element = queue->array[queue->head];
    queue->head = get_index(queue, 1);
    queue->count--;

    return element;
}

void queue_print(queue_t* queue, void (*print_item)(void* item))
{
    if (queue == NULL || print_item == NULL)
        return;

    printf("[");
    for (int i = 0; i < queue->count; i++)
    {
        print_item(queue->array[get_index(queue, i)]);

        if (i < queue->count - 1)
            printf(", ");
    }
    printf("]\n");
}

static int get_index(queue_t* queue, int i)
{
    return (queue->head + i) % queue->capacity;
}