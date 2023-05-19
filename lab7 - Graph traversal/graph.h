struct adj_list_node {
    int v;
    struct adj_list_node* next;
};

struct adj_list {
    struct adj_list_node* head;
};

struct graph {
    int V;
    struct adj_list* adj_list;
};

struct adj_list_node* create_node(int v);
struct graph* create_graph(int V);

void addEdge(struct graph* graph, int src, int dest);