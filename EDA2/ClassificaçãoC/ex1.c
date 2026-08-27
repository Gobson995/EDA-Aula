#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
int vetor[N];

void quicksort(int i, int n) {
    if (i >= n) return;

    int pivo = vetor[n];
    int j = i;
    for (int k = i; k < n; k++) {
        if (vetor[k] <= pivo) {
            int aux = vetor[k];
            vetor[k] = vetor[j];
            vetor[j] = aux;
            j++; 
        }
    }
    
    int aux = vetor[n];
    vetor[n] = vetor[j];
    vetor[j] = aux;


    quicksort(i, j-1);
    quicksort(j+1, n);
}

int main () {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vetor[i] = rand() % 20;
    }

    quicksort(0, N-1);

    for (int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
    return 0;
}