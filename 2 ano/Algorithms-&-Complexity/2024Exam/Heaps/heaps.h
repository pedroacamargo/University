#define MAX 1000
typedef struct prQueue {
    int values[MAX];
    int size;
} PriorityQ;

void printHeap(int v[]);
void bubbleup(int v[], int i);
void bubbledown(int v[], int i);
void swap(int v[], int i, int j);


/**
 * Using Struct
*/
void initPriorityQ(PriorityQ *q);
int add(PriorityQ *q, int x);
int remove(PriorityQ *q, int *x);
void heapify(int v[], int N);