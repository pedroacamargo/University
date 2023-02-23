#include <stdio.h>
#include <stdlib.h>

#define ABORTAR(mensagem) { printf("%s\n", mensagem); abort(); }

#define VE_SE_E_MAIOR(qual) {\
	if(scanf("%d", &valor) != 1) ABORTAR("Nao consegui ler um valor!");\
	if(valor > maior) {\
		maior = valor;\
		ordem = qual;\
		printf("valor = %d\n", valor);\
	}\
}

int main() {
	int maior =0;
	int ordem = 0;
	int valor;

	VE_SE_E_MAIOR(1)
	VE_SE_E_MAIOR(2)
	VE_SE_E_MAIOR(3)
	VE_SE_E_MAIOR(4)
	VE_SE_E_MAIOR(5)


	printf("%d\n", ordem);
	return 0;
}



// gcc -e 