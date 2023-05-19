#include <stdio.h>
#include <limits.h>
#include "graph.h"

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

void print_step(int k, int *dist, int *relaxed_u, int *relaxed_v, int nr_relaxed, int V)
{
        printf("%d: relaxed %d edges: ", k + 1, nr_relaxed);
        for (int i = 0; i < nr_relaxed; i++) {
            printf("(%d, %d) ", relaxed_u[i] + 1, relaxed_v[i] + 1);
        }
        printf("\nu | ");
        for (int i = 0; i < V; i++) {
            printf("%d ", i + 1);
        }
        printf("\nd | ");
        for (int i = 0; i < V; i++) {
            if (dist[i] != INT_MAX)
                printf("%d ", dist[i]);
            else
                printf("- ");
        }
        printf("\n\n");
}

void bellman_ford(struct graph* graph, int src)
{
    int dist[NR_VERTICES];
    int parent[NR_VERTICES];

    for (int v = 0; v < graph->V; v++)
    {
        dist[v] = INT_MAX;
        parent[v] = -1;
    }
    dist[src] = 0;

    for (int k = 0; k < graph->V - 1; k++) {
        int nr_relaxed = 0;
        int relaxed_u[NR_VERTICES];
        int relaxed_v[NR_VERTICES];

        for (int i = 0; i < graph->V; i++) {
            struct adj_list_node* current = graph->adj_list[i].head;
            while (current) {
                int j = current->v;
                if (dist[j] > dist[i] + current->weight && dist[i] != INT_MAX) {
                    dist[j] = dist[i] + current->weight;
                    parent[j] = i;

                    relaxed_u[nr_relaxed] = i;
                    relaxed_v[nr_relaxed] = j;
                    nr_relaxed++;
                }

                current = current->next;
            }
        }

        print_step(k, dist, relaxed_u, relaxed_v, nr_relaxed, graph->V);

        if (nr_relaxed == 0)
            break;
    }

    print_result(dist, parent, NR_VERTICES);
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

    bellman_ford(graph, get_node(1));

    return 0;
}