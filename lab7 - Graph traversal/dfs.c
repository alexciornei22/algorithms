#include <stdio.h>
#include <malloc.h>

#include "graph.h"

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
int d[NR_VERTICES];
int f[NR_VERTICES];

void explore(int u, struct graph* graph, int* time) {
    *time = *time + 1;
    d[u] = *time;
    colors[u] = GRAY;

    struct adj_list_node* current = graph->adj_list[u].head;
    while (current) {
        int v = current->v;

        if (colors[v] == WHITE) {
            parents[v] = u;
            explore(v, graph, time);
        }

        current = current->next;
    }

    *time = *time + 1;
    f[u] = *time;
    colors[u] = BLACK;
}

void dfs(struct graph* graph)
{
    for (int i = 0; i < graph->V; i++) {
        colors[i] = WHITE;
        parents[i] = -1;
        d[i] = 0;
        f[i] = 0;
    }
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
    int time = 0;

    for (int i = 0; i < graph->V; i++) {
        if (colors[i] == WHITE) {
            explore(i, graph, &time);
        }
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

    dfs(graph);

    for (int i = 0; i < graph->V; i++) {
        char c = i + 65;
        printf("%c: d[%c] = %d, f[%c] = %d\n",
            c, c, d[i], c, f[i]);
    }
    return 0;
}