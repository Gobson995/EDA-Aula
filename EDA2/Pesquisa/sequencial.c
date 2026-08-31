#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pesquisaSequencial(int chave, int v[], int n) {
    int contador = 0;

    for (int i = 0; i < n; i++) {
        contador += 2;
        if (v[i] == chave) {
            return contador;
        }
    }

    contador++;

    return contador;
}

int main () {
    int n;
    scanf("%d", &n);

    int v[n];

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % n;

        printf("v[%d] = %d\n", i, v[i]);
    }

    int chave;
    scanf("%d", &chave);

    int resp = pesquisaSequencial(chave, v, n);

    printf("Foi feito %d comparacoes.\n", resp);
}