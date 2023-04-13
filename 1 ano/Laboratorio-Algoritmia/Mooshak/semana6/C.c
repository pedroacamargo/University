#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int numero;
  char dificuldade;
  int preco;
} Pedido;


void sort(Pedido *request, int N) {
    Pedido aux;
    int res = 0;

    // this function section will compare the j and j + 1 elements to apply the bubble sort in the given array
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-i-1; j++) {
          
            if (request[j].preco != request[j+1].preco) res = request[j].preco - request[j+1].preco;
            else if (request[j].dificuldade != request[j+1].dificuldade) res = request[j+1].dificuldade - request[j].dificuldade;
            else res = request[j+1].numero - request[j].numero;

            if (res < 0) {
                aux = request[j];
                request[j] = request[j+1];
                request[j+1] = aux;
            }
        }
    }
}

int main() {
  int N;
  if (scanf("%d",&N) != 1) return 1;
  Pedido pedidos[N];
  for (int i = 0; i < N; i++) {
    int pedido = 0, preco = 0;
    char nivel;
    if (scanf("%d",&pedido) != 1) return 1;
    getchar();
    if (scanf("%c",&nivel) != 1) return 1;
    if (scanf("%d",&preco) != 1) return 1;
    pedidos[i] = (Pedido)  { .numero = pedido, .dificuldade = nivel, .preco = preco}; // this will add the created struct in an array pedidos
  } 
  
  sort(pedidos,N);

  for (int k = 0; k < N; k++) {
    printf("%d %c %d\n",pedidos[k].numero,pedidos[k].dificuldade,pedidos[k].preco);
  }

  return 0;
}
