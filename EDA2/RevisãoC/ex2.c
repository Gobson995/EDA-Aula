#include <stdio.h>

int main () {
    int v;
    scanf("%d", &v);

    int vetor[v];
    int prod = 1;
    

    for (int i = 0; i < v; i++) {
        scanf("%d", &vetor[i]);
        prod *= vetor[i]; 
    }

    int resp[v];

    for (int i = 0; i < v; i++) {
        resp[i] = prod / vetor[i];
    }

    for (int i = 0; i < v; i++) {
        printf(" %d", resp[i]);
    }

    printf("\n");
    return 0;
}