#include <stdio.h>
#include <string.h>

// 3
// 1
// 2
// 5
// 4





int main() {
   char posicao[8]; // 31254

   if (scanf("%s", posicao) != 1) return 1;

   int lengthPosicao = strlen(posicao);

   char stringFull[1000] = "AMAEREUNMI TOMCEMATAG ASAEPARENA CANRAADET AOHPRGEAE";
   char string[1000] = "AMAEREUNMI TOMCEMATAG ASAEPARENA CANRAADET AOHPRGEAE";


   // Extract the first token
   char * token = strtok(string, " ");
   
   printf( " %s\n", token ); //printing the token
   printf( " %s\n", stringFull ); //printing the token

   int order = 0;

   // reorder the array
   for (int i = 0; i < lengthPosicao;i++) {
      // convert to int
      order = posicao[i] - '0'; 

      for (order;order > 1;order--) {
         token = strtok(NULL, " ");
      }
      
      token = strtok(string, " ");
      printf("%s\n",token);
      
   }

   return 0;
}