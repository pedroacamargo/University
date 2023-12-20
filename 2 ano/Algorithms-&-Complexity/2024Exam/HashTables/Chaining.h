#define HSIZE 1000

typedef struct bucket {
    int key;
    int value;
    struct bucket *next;
} *Bucket;

typedef Bucket HashTableChain[HSIZE];

int hash(int key, int size);
void initTab(HashTableChain h);
int lookup(HashTableChain h, int k, int *i);
int update(HashTableChain h, int k, int i);
int removeKey(HashTableChain h, int k);