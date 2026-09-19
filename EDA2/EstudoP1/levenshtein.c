#include <stdio.h>
#include <string.h>

int min(int a, int b, int c) {
    int minimo = a;

    if (minimo > b) {
        minimo = b;
    }

    if (minimo > c) {
        minimo = c;
    }

    return minimo;
}

int main() {
    char A[100];
    char B[100];

    scanf("%s", A);
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    int M[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        M[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        M[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int custo;

            if (A[i - 1] == B[j - 1]) custo = 0;
            else custo = 1;

            M[i][j] = min(
                M[i - 1][j] + 1,
                M[i - 1][j - 1] + custo,
                M[i][j - 1] + 1
            );
        }
    }

    printf("%d\n", M[m][n]);

    return 0;
}