#include <stdio.h>

int main () {
    int v, k;
    scanf("%d %d", &v, &k);

    int vetor[v];
    for (int i = 0; i < v; i++) {
        scanf("%d", &vetor[i]);
    }

    int resp[v-k+1];

    for (int i = 0; i < v-k+1; i++) {
        int max = vetor[i];

        for (int j = 1; j < k; j++) {
            if (vetor[i+j] > max) max = vetor[i+j];
        }

        resp[i] = max;
    }

    for (int i = 0; i < v-k+1; i++) {
        printf("%d ", resp[i]);
    }

    printf("\n");

    return 0;
}