#include <stdio.h>

// função para acabar com as dizimas
int repete(int array[], int tamanho) {
  int repeatingStart = -1;

  for (int i = 0; i < tamanho; i++) {
    for (int j = i+1; j < tamanho; j++) {
      if (array[i] == array[j]) {
        repeatingStart = j;
        array[j] = -1;
        return j;
      }
    }
    if (repeatingStart != -1) {
      break;
    }
  }

  return tamanho;

}

int main() {
  
  int N = 0;
  int K = 0;
  int I = 0;
  int index = 0;
  if (scanf("%d",&N) != 1) return 1;
  int res[N][101];
  int Ks[N]; // array com todos numeros de guiches por linha

  for (int i = 0; i < N; i++) {

    if (scanf("%d", &K) != 1) return 1; // numero de gichês

    if (scanf("%d", &I) != 1) return 1; // gichê inicial
    int giches[100];
    Ks[i] = K;

    // adicionar num array os casos, para ficar pulando entre eles
    // 3 1 4 2
    while (index < K) {
      int giche = 0;
      if (scanf("%d",&giche) != 1) return 1;
      giches[index] = giche;

      index++;
    }

    // giches = {3, 1, 4, 2}
    // res = {{},{}}
    int indexGiches = -1;
    int debug = 0;

    for (int j = 0; j <= K; j++) {

      if (indexGiches == 0) {
        Ks[i] = j - 1;
        debug = 1; // o debug é para mudar o numero final de caracteres para colocar no output
        break;
      }

      if (j == K) {
        res[i][K] = -1; // if == -1, printf("CICLO INFERNAL");
        break;
      }

      if (j == 0) {

        indexGiches = giches[I - 1];
        res[i][0] = I; // printf("%d ",indexGiches);
      } else if (j < K) {
        res[i][j] = indexGiches; // printf("%d ",indexGiches);
        indexGiches = giches[indexGiches - 1];
      }
    }
    int max = repete(res[i],K);
    if (debug == 1) {
      index = 0;
      debug = 0;
      continue;
    } else {
      if (max < K) Ks[i] = max;
    }
    index = 0; 
  }
  
  // output
  for (int g = 0; g < N; g++) {
    for (int h = 0; h <= Ks[g]; h++) {
      if (res[g][h] == -1) {
        printf("CICLO INFERNAL");
      } else {
        if (Ks[g] == h) {
          printf("%d",res[g][h]);
          break;
        }
        if (res[g][h] == 0) break;
        if (Ks[g] != h) printf("%d ",res[g][h]);
      }
    }

    printf("\n");
  } 
  return 0;
}
