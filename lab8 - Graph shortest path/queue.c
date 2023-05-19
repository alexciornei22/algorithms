#include "queue.h"
#include <malloc.h>
#include <limits.h>

struct queue* create_queue(int n)
{
    struct queue* q = malloc(sizeof(struct queue));
    q->v = calloc(n, sizeof(struct pair));
    q->size = 0;

    return q;
}

void free_queue(struct queue* q)
{
    free(q->v);
    free(q);
    q = NULL;
}

void enqueue(struct queue* q, int key)
{
    q->v[q->size].v = key;
    q->v[q->size].d = INT_MAX;
    q->size++;
}

struct pair dequeue(struct queue* q)
{
    int pos;
    int minn = INT_MAX;

    for (int i = 0; i < q->size; i++) {
        if (q->v[i].d < minn) {
            minn = q->v[i].d;
            pos = i;
        }
    }

    struct pair p = q->v[pos];

    for (int i = pos; i < q->size - 1; i++) {
        q->v[i] = q->v[i + 1];
    }
    q->size--;

    return p;
}

struct pair* get_pair(struct queue* q, int key)
{
    for (int i = 0; i < q->size; i++) {
        if (q->v[i].v == key)
            return &q->v[i];
    }

    return NULL;
}

void print_queue(struct queue* q)
{
    printf("Q | ");
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->v[i].v + 1);
    }
    printf("\n");

    printf("d | ");
    for (int i = 0; i < q->size; i++) {
        if (q->v[i].d != INT_MAX)
            printf("%d ", q->v[i].d);
        else
            printf("- ");
    }
    printf("\n\n");
}

int is_empty(struct queue* q)
{
    return q->size == 0;
}