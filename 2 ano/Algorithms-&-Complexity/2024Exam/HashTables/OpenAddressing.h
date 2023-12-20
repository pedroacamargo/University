#define HSIZE 1000
#define STATUS_FREE 0
#define STATUS_USED 1

typedef struct bucket {
    int status;
    int key;
    int value;
} Bucket;
typedef Bucket HashTable[HSIZE];

/**
 * @def Hash Function
*/
int hash(int key, int size);

/**
 * @def Linear Probing 
 * No caso de querermos guardar um par numa dada posição p já ocupada, tentamos fazê-lo na posição seguinte.
 * Se esta também estiver sido ocupada, repetimos o processo até que seja atingida uma posição não ocupada.
*/
int find_probe(HashTable h, int k);

void initTab(HashTable h);
int lookup(HashTable h, int k, int *i);
int update(HashTable h, int k, int i);

/**
 * @def Quadratic Probing
 * Em vez de tentarmos procurar na posição imediatamente seguinte, vamos procurar d posições à frente, incrementando esta medida d.
 * É uma forma de evitar os clusters de células ocupadas (aumentando por isso o número de colisões) utilizando linear probing.
*/
int find_Quad_probe(HashTable h, int k);