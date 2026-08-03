#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct teste { 
    int inteiro;
    float real;
    char nome[30];
} informacao;

int main(void) {            
    informacao *p, x = {321, 2.39, "Silva"};
    
    // p = (struct teste *) malloc(sizeof(struct teste)); // ERRO LÓGICO: Malloc inútil (vazamento de memória)
    p = &x; // Correto: O ponteiro apenas recebe o endereço de x. 
    
    printf("Campos da variável x: %i, %f, %s\n", p->inteiro, p->real, p->nome); 
    
    return 0;
}