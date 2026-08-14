#include <stdio.h>

int main () {
    int n;
    scanf("%d", &n);

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    int dp[n];

    dp[0] = 1;
    dp[1] = 2;

    for (int i = 2; i < n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    printf("%d\n", dp[n-1]);

    return 0;
}