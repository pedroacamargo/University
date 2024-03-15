#include <stdio.h>
#include "mysystem.h"

int main() {

	char comando1[] = "ls -l -a -h";
	char comando2[] = "sleeep 30";
	char comando3[] = "sleep 10";
	char comando4[] = "ps";
	int ret;


	printf("\nCOMANDO 1: a executar mysystem para %s\n",comando1);
	ret = mysystem(comando1);
	printf("COMANDO 1: ret = %d\n",ret);

	printf("\nCOMANDO 2: a executar mysystem para %s\n",comando2);
	ret = mysystem(comando2);
	printf("COMANDO 2: ret = %d\n",ret);

	printf("\nCOMANDO 3: a executar mysystem para %s\n",comando3);
	ret = mysystem(comando3);
	printf("COMANDO 3: ret = %d\n",ret);

	printf("\nCOMANDO 4: a executar mysystem para %s\n",comando4);
	ret = mysystem(comando4);
	printf("COMANDO 4: ret = %d\n",ret);

	return 0;
}