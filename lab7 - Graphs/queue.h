struct queue_node
{
    int key;
    struct queue_node* next;
};


struct queue
{
    struct queue_node* front;
    struct queue_node* rear;
};

struct queue* create_queue();

void enqueue(struct queue* queue, int key);

int dequeue(struct queue* queue);

int is_empty(struct queue* queue);