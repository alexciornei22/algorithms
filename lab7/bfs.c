#include <stdio.h>
#include <malloc.h>

#include "graph.h"
#include "queue.h"

#define NR_VERTICES 10

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9

#define WHITE 0
#define GRAY 1
#define BLACK 2

int colors[NR_VERTICES];
int parents[NR_VERTICES];
int dist[NR_VERTICES];

void bfs(int src, struct graph* graph)
{
    for (int i = 0; i < graph->V; i++) {
        colors[i] = WHITE;
        parents[i] = -1;
        dist[i] = -1;
    }

    struct queue* queue = create_queue();
    enqueue(queue, src);
    colors[src] = GRAY;
    dist[src] = 0;

    while (!is_empty(queue))
    {
        int u = dequeue(queue);

        struct adj_list_node* current = graph->adj_list[u].head;
        while (current) {
            int v = current->v;

            if (colors[v] == WHITE) {
                dist[v] = dist[u] + 1;
                parents[v] = u;
                colors[v] = GRAY;
                enqueue(queue, v);
            }
            current = current->next;
        }

        colors[u] = BLACK;
    }
}

int main()
{
    struct graph* graph = create_graph(NR_VERTICES);
    addEdge(graph, A, B);
    addEdge(graph, A, C);
    addEdge(graph, A, H);

    addEdge(graph, B, D);
    addEdge(graph, B, E);
    addEdge(graph, B, H);
    addEdge(graph, B, I);

    addEdge(graph, C, D);

    addEdge(graph, D, E);
    addEdge(graph, D, J);

    addEdge(graph, E, F);
    addEdge(graph, E, G);

    addEdge(graph, F, G);

    addEdge(graph, H, I);

    addEdge(graph, I, A);

    bfs(A, graph);

    for (int i = 0; i < graph->V; i++) {
        char c = i + 65;
        printf("%c: dist[A, %c] = %d, p[%c] = %c\n",
            c, c, dist[i], c, parents[i] + 65);
    }

    return 0;
}