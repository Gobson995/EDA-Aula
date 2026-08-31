#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pesquisaSequencialSentinela(int chave, int v[], int n) {
    int i = 0;
    int contador = 2;

    v[n] = chave;

    while (v[i] != chave) {
        i++;
        contador++;
    }

    if (i < n) return contador;


    return -1;
}

int main () {
    int n;
    scanf("%d", &n);

    int v[n+1];

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % n;

        printf("v[%d] = %d\n", i, v[i]);
    }

    int chave;
    scanf("%d", &chave);

    int resp = pesquisaSequencialSentinela(chave, v, n);

    if (resp == -1) resp = n + 2;
    printf("Foi feito %d comparacoes.\n", resp);
}