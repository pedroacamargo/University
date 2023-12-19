/**
 * @def Static Array Queues
*/
#define MAX 1000
typedef struct queue {
    int values[MAX];
    int inicio, tamanho;
} Queue;

void initQueue(Queue *q);
int enqueue(Queue *q, int value);
int dequeue(Queue *q);


/**
 * @def Linked Lists Queues
*/
typedef struct celula {
    int value;
    struct celula *prox;
} Celula;
typedef struct queue {
    struct celula *inicio, *fim;
} QueueL;

void initQueueL(QueueL *q);
int enqueueL(QueueL *q, int value);
int dequeueL(QueueL *q);