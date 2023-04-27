#include <malloc.h>
#include "queue.h"

struct queue* create_queue()
{
    struct queue* queue = malloc(sizeof(struct queue));
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void enqueue(struct queue* queue, int key)
{
    struct queue_node* new_node = malloc(sizeof(struct queue_node));
    new_node->key = key;
    new_node->next = NULL;

    if (is_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

int dequeue(struct queue* queue)
{
    if (is_empty(queue))
        return -1;

    struct queue_node* node = queue->front;
    int key = node->key;

    queue->front = node->next;
    if (queue->front == NULL)
        queue->rear = NULL;

    free(node);
    return key;
}

int is_empty(struct queue* queue)
{
    if (queue->front == NULL)
        return 1;
    return 0;
}