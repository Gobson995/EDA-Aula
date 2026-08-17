#include <stdio.h>
#include <string.h>

int main () {
    int s[100];
    int n;

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }
    int total = 1 << n;

    for (int i = 0; i < total; i++) {
        printf("[");
        int imprimiualgo = 0;

        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                if (imprimiualgo) printf(", ");

                printf("%d", s[j]);
                imprimiualgo = 1;
            }
        }

        printf("]\n");
    }

    return 0;
}