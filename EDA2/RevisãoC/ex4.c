#include <stdio.h>

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int main() {
    int v;
    scanf("%d", &v);

    int vetor[v];
    
    for (int i = 0; i < v; i++) {
        scanf("%d", &vetor[i]);
    }

    int dp[v];

    dp[0] = max(0, vetor[0]);

    if (v > 1) {
        dp[1] = max(dp[0], vetor[1]);
    }

    for (int i = 2; i < v; i++) {
        int opcaoA = dp[i-1];
        int opcaoB = dp[i-2] + vetor[i];

        dp[i] = max(opcaoA, opcaoB);
    }

    printf("%d\n", dp[v-1]);

    return 0;
}