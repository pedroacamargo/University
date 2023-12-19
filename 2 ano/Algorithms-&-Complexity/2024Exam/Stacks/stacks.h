/**
 * @def Using static arrays
*/
#define MAX 1000
typedef struct stack {
    int values[MAX];
    int sp;
} Stack;

void initStack(Stack *s);
int push(Stack *s, int value);
int pop(Stack *s);



/**
 * @def Using Linked Lists
*/
typedef struct celula {
    int value;
    struct celula *prox;
} Celula, *StackL;

void initStackL(StackL *s);
int pushL(StackL *s, int value);
int popL(StackL *s);


/**
 * @def Using Dinamic Arrays
*/
typedef struct stack {
    int size;
    int *values;
    int sp;
} StackD;
void initStackD(StackD *s, int n);
int pushD(StackD *s, int x);
int popD(StackD *s);
int doubleArray(StackD *s);