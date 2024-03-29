#include <stdio.h>

typedef struct LInt_nodo {
	int valor;
	struct LInt_nodo *prox;
} *LInt;

typedef struct nodo{
	int valor;
	struct nodo*pai,*esq,*dir;
} *ABin;

/* Questão 1 */
// conta quantas parcelas tem um somatório
int numero_parcelas (int n){
	int r = 0;
	int count = 0;

	while(n != 1){
		r += n;
		if(n%2 == 0)
			n /= 2;
		else 
			n = 1 + (3*n);

		count += 1;
	}
	
	return count;
}

//função swap
void swap(int array[], int indice1, int indice2){
	int temp;

	temp = array[indice1];
	array[indice1] = array[indice2];
	array[indice2] = temp;

}

//função que dá a 100ª menor parcela
int sumhtpo(int n){
	int i = 0;  // index
	int numero_de_parcelas = numero_parcelas(n); // numero de parcelas
	int array[numero_de_parcelas]; // inicialização do array para colocar todas as parcelas

	// caso em que há menos do que 100 parcelas
	if(numero_de_parcelas < 100)
		return -1;

	// preenchimento do array
	while(n != 1){
		if(n%2 == 0){
			n /= 2;
			array[i] = n;
		} else { 
			n = 1 + (3*n);
			array[i] = n;
		} 
		i++;
	}

	// ordenação do array  (Selection Sort)
	int j;

	for(i=0; i<numero_de_parcelas; i++)
		for(j=i; j<numero_de_parcelas; j++)
			if( array[i] > array[j] )
				swap(array, i, j);

	return array[99];
}


/* Questão 2 */
int verifica_multimodal(int v[], int N, int freq, int indice_da_moda){
	int count = 1; 
	int i, j;

	for(i=0; i<N; i++){
		for(j = i+1; j<N; j++){
			if(v[i] == v[j])
				count++;
		}

		if(count == freq && v[i] != v[indice_da_moda])
			return 1; // é multimodal
		
		count = 1;
	} 

	return 0;	// não é multimodal
}

int moda(int v[], int N, int *m){
	// conjunto vazio
	if(N == 0)
		return 0;
	
	// declarando variáveis
	int i, j, indice_da_moda, freq = 1, count = 1;

	// achar a moda do conjunto
	for(i = 0; i<N; i++){
		for(j = i+1; j<N; j++){
			if(v[i] == v[j])
				count++;
		}
		// verificar se as ocorrências em v[i] são maiores que as anteriores
		if(count > freq){
			indice_da_moda = i;
			freq = count;
		}
		// refresh ao contador
		count = 1;
	}

	//verificar se o conjunto é multi-modal
	int verifica = verifica_multimodal(v, N, freq, indice_da_moda);

	if(verifica == 1)
		return 0;	// é multimodal
	else
		return (*(m + indice_da_moda));  // não é multimodal 
}

/* Questão 3 */
int procura(LInt *l, int x) {
    LInt head = *l;
    LInt move = *l;
    LInt ant = *l;
    if (!l) return 0;
    else if (!(head->prox)) {
        if (head->valor == x) return 1;
        else return 0;
    }

    while (move && move->valor != x) {
        ant = move;
        move = move->prox;
    }

    if (move->valor == x) {
        ant->prox = NULL;
        move->prox = head;
        l = &move;
        return 1;
    }

    return 0;

}

/* Questão 4 */
int freeAB(ABin a){
	int r = 0;

	if(!a)
		return 0;
	else {
		r = 1 + freeAB(a->esq) + freeAB(a->dir);
		free(a);
	}


	return r;
}

/* Questão 4 */
void caminho(ABin a) {
   
    if (a && a->pai) {
        if(a->pai->esq->valor == a->valor) {
             caminho(a->pai);
             printf("esq");
        }
        else if(a->pai->dir->valor == a->valor) {
             caminho(a->pai);
             printf("dir");
        }
     }


}


int main(){
    
    return 0;
}