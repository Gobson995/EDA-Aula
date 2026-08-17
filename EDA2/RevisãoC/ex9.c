#include <stdio.h>
#include <string.h>

int main () {
    char s[100];

    scanf(" %[^\n]", s);

    int tamanho = strlen(s);

    char c = s[0];
    int contador = 0;

    char resposta[200] = "";

    for (int i = 0; i < tamanho; i++) {
        if (i == tamanho - 1) {
            int tr = strlen(resposta);
            contador++;
            char numero = contador + '0';
            resposta[tr] = numero;
            resposta[tr + 1] = c;
            resposta[tr + 2] = '\0';
        }

        if (s[i] == c) contador++;
        else {
            int tr = strlen(resposta);
            char numero = contador + '0';
            resposta[tr] = numero;
            resposta[tr + 1] = c;

            c = s[i];
            contador = 1;
        }
    }

    printf("%s\n", resposta);

    return 0;
}