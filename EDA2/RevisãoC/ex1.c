#include <stdio.h>

int main () {
    int v, k;
    scanf("%d %d", &v, &k);

    int vetor[v];
    int resp;
    int verifica[v];

    for (int i = 0; i < v; i++) {
        scanf("%d", &vetor[i]);
        verifica[i] = k - vetor[i]; 
    }

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (verifica[i] == vetor[j] && i != j) {
                resp++;
                break;
            }
        }
        if (resp > 0) {
            printf("True");
            return 0;
        }
    }

    printf("False");
    return 0;
}