#include <stdio.h>

int main () {
    int v;
    scanf("%d", &v);

    int vetor[v+1];
    int verifica[v+1];
    verifica[0] = 0;
    
    for (int i = 1; i <= v; i++) {
        scanf("%d", &vetor[i]);
        verifica[i] = 0;
    }

    for (int i = 1; i <= v; i++) {
        if (vetor[i] <= 0) verifica[0] = 0;
        else verifica[vetor[i]] = vetor[i];
    }

    for (int i = 1; i <=v; i++) {
        if (verifica[i] == 0) {
            printf("%d\n", i);
            break;
        }
        
    }

    return 0;   
    
}