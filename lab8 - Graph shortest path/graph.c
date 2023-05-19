#include <malloc.h>
#include "graph.h"

struct adj_list_node* create_node(int v, int weight)
{
    struct adj_list_node* new_node = malloc(sizeof(struct adj_list_node));
    new_node->v = v;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

struct graph* create_graph(int V)
{
    struct graph* graph = malloc(sizeof(struct graph));
    graph->V = V;
    graph->adj_list = calloc(V, sizeof(struct adj_list));

    for (int i = 0; i < V; i++)
        graph->adj_list[i].head = NULL;

    return graph;
}

void addEdge(struct graph* graph, int src, int dest, int weight)
{
    struct adj_list_node* new_node = create_node(dest, weight);

    struct adj_list_node* current = graph->adj_list[src].head;

    if (current == NULL) {
        graph->adj_list[src].head = new_node;
    } else {
        while (current->next) {
            current = current->next;
        }

        current->next = new_node;
    }
}