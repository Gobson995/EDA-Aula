#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct teste { 
    int inteiro;
    float real;
    char nome[30];
} informacao;


 main(void) {            
    informacao *p, x = {321, 2.39, "Silva"};
    p = &x; // agora aponta para alguma coisa
    // p = (struct teste *) malloc(sizeof(struct teste)); não precisa mais
    printf("Campos da variável x: %i, %f, %s", p->inteiro, p->real, p->nome);
}