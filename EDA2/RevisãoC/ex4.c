#include <stdio.h>

int main() {
    int v;
    scanf("%d", &v);

    int vetor[v];
    int soma = 0;
    int ind[v];
    
    for (int i = 0; i < v; i++) {
        scanf("%d", &vetor[i]);
        soma += vetor[i];
        ind[i] = 0;
    }

    ind[0] = 1;
    int ver = soma - vetor[0];

    for (int i = 1; i < v; i++) {
        if (soma - vetor[i] < ver) {
            ind[i] = 1
        }
    }
}