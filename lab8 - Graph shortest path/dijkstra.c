#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "queue.h"

#define NR_VERTICES 7

int get_node(int v)
{
    return v - 1;
}

void print_result(int* d, int* p, int n)
{
    printf("u | ");
    for (int i = 0; i < n; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    printf("d | ");
    for (int i = 0; i < n; i++) {
        printf("%d ", d[i]);
    }
    printf("\n");

    printf("p | ");
    for (int i = 0; i < n; i++) {
        printf("%d ", p[i] + 1);
    }
    printf("\n");
}

void dijkstra(struct graph *graph, int src)
{
    struct queue *queue = create_queue(NR_VERTICES);
    int dist[NR_VERTICES];
    int parent[NR_VERTICES];

    for (int v = 0; v < graph->V; v++)
    {
        enqueue(queue, v);
        parent[v] = -1;
    }
    queue->v[src].d = 0;

    print_queue(queue);

    while (!is_empty(queue))
    {
        struct pair p = dequeue(queue);
        dist[p.v] = p.d;

        struct adj_list_node *current = graph->adj_list[p.v].head;
        while (current)
        {
            int v = current->v;
            struct pair *curr_pair = get_pair(queue, v);

            if (curr_pair != NULL && curr_pair->d > p.d + current->weight) {
                curr_pair->d = p.d + current->weight;
                parent[curr_pair->v] = p.v;
            }

            current = current->next;
        }
        print_queue(queue);
    }

    print_result(dist, parent, NR_VERTICES);

    free_queue(queue);
}

int main()
{
    struct graph *graph = create_graph(NR_VERTICES);

    addEdge(graph, get_node(1), get_node(2), 3);
    addEdge(graph, get_node(1), get_node(3), 4);
    addEdge(graph, get_node(1), get_node(5), 1);
    addEdge(graph, get_node(1), get_node(6), 10);
    addEdge(graph, get_node(1), get_node(7), 3);

    addEdge(graph, get_node(2), get_node(3), 2);

    addEdge(graph, get_node(3), get_node(4), 2);
    addEdge(graph, get_node(3), get_node(6), 2);

    addEdge(graph, get_node(5), get_node(4), 3);
    addEdge(graph, get_node(5), get_node(7), 1);

    addEdge(graph, get_node(6), get_node(4), 2);

    addEdge(graph, get_node(7), get_node(3), 1);
    addEdge(graph, get_node(7), get_node(4), 10);
    addEdge(graph, get_node(7), get_node(5), 2);

    dijkstra(graph, get_node(1));

    return 0;
}