#include <stdio.h>

typedef struct teste {
    int numero;
    float altura;
    char nome[30];
} testando;

int main () {
    testando *p, x = {10, 1.70, "Gustavo"};

    if (p) {
        printf("Não tem nada, nem null, mas é TRUE\n"); // a saida vai dar true, pois não tem nada dentro do p* (ele pega um valor qualquer)
                                                        // mas o meu UBUNTU faz ele dar false, pois inicia com tudo zerado antes de rodar o codigo
    }
    else {
        printf("P é FALSE\n");
    }

    return 0;
}