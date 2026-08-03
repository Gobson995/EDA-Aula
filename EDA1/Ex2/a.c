#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct teste { 
    int inteiro;
    float real;
    char nome[30];
} informacao;


main(void) {
    informacao *p = NULL; // limpa o lixo da memoria
    informacao x = {321, 2.39, "Silva"};
    p = &x; // faz apontar para o lugar certo
    if (p) { 
        printf("dponteiro inicializado corretamente \n");
        printf("valores da struct X: %i, %f, %s", p->inteiro, p->real, p->nome);
    }
    else printf("o ponteiro está anulado");
}        