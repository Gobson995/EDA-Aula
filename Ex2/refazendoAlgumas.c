#include <stdio.h>
#include <stdlib.h>

typedef struct teste { 
    int inteiro;
    float real;
    char nome[30];
} informacao;

int main(void) {            
    informacao *p, x = {321, 2.39, "Silva"};
    
    // 1. Cria a casa nova no Heap e guarda o endereço em 'p'
    p = (struct teste *) malloc(sizeof(struct teste));
    
    // 2. A MÁGICA: O asterisco faz o C copiar todo o conteúdo 
    // da casa 'x' para dentro da casa nova apontada por 'p'
    *p = x; 
    
    // Agora sim, imprime com sucesso os valores copiados!
    printf("Campos da variável x: %i, %f, %s\n", p->inteiro, p->real, p->nome); 
    
    // Como usamos malloc, a boa prática exige liberar no final
    free(p);
    
    return 0;
}