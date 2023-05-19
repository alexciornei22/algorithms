struct pair {
    int v;
    int d;
};

struct queue
{
    struct pair *v;
    int size;
};

struct queue* create_queue(int n);

void free_queue(struct queue* queue);

void enqueue(struct queue* queue, int key);

struct pair dequeue(struct queue* queue);

struct pair* get_pair(struct queue* q, int key);

void print_queue(struct queue* q);

int is_empty(struct queue* queue);