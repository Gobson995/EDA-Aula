#include <stdio.h>

int main () {
    int n;

    scanf("%d", &n);

    int vet[n];
    int flag[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &vet[i]);
        flag[i] = 0;
    }

    int resp = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (vet[i] == vet[j] && flag[i] == 0 && flag[j] == 0) {
                resp++;
                flag[i] = 1;
                flag[j] = 1;
                break;
            }
        }
    }

    printf("%d pares\n", resp);

    return 0;
}