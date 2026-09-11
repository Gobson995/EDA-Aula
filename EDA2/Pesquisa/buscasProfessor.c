#include <stdio.h>
#include <stdlib.h>

int compara(const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int* geraVetor(int n) {
    int* v = malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < n; i++) {
        v[i] = rand() % n;
    }

    qsort(v, n, sizeof(int), compara);

    return v;
}


int pesquisaSequencial(int chave, int v[], int n) {
    int i, contador = 1;
    for (i = 0; i < n; i++) {
        contador++;
        if (v[i] == chave) {
            return contador;
        }
        contador++;
    }
    return contador; //índice inválido
}

int pesquisaSequencialSentinela(int chave, int v[], int n) {
    int i = 0, contador = 1;
    v[n] = chave; //A última posição do vetor possui o sentinela
    while (v[i] != chave) {
        i++;
        contador++;
    }
    contador++;
    if (i < n) {
        return contador;
    }
    return contador; //Índice inválido
}

int pesquisaBinaria(int chave, int v[], int n) {
    int inicio = 0, fim = n - 1, contador = 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        contador++;
        if (chave == v[meio]) {
            return contador;    
        } else if (chave < v[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
        contador+=2;
    }
    return contador; //Índice invalido
}

int pesquisaInterpolacao(int chave, int v[], int n) {
  int inicio = 0, meio, fim = n - 1;
  int contador = 3;
  while (inicio <= fim && chave >= v[inicio] && chave <= v[fim]) {
    contador++;
    if (inicio == fim) return v[inicio] == chave ? contador : contador;
    meio = inicio + (((double) (fim - inicio) / (v[fim] - v[inicio])) * (chave - v[inicio]));
    contador++;
    if (chave == v[meio]) {
      return contador;
    } else if (chave < v[meio]) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
    contador += 4;
  }
  return contador; //Índice impossível
}


int main() {
    int tamanhos[] = {1000, 5000, 10000, 50000, 100000};
    int num_tamanhos = 5;

    printf("N,Sequencial,Sentinela,Binaria,Interpolacao\n");

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        int* v = geraVetor(n);
        
        int medio = v[rand() % n]; 

        int seq = pesquisaSequencial(medio, v, n);
        int sen = pesquisaSequencialSentinela(medio, v, n);
        int bin = pesquisaBinaria(medio, v, n);
        int inter = pesquisaInterpolacao(medio, v, n);

        printf("%d,%d,%d,%d,%d\n", n, seq, sen, bin, inter);

        free(v); 
    }
    return 0;
}