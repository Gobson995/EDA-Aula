#include <stdio.h>

typedef struct teste { 
    int inteiro;
    float real;
    char nome[30];
} informacao;

int main(void) {
    int a = 10;
    int vet[] = {1, 2, 3, 4, 5}; 
    float b = 35.75;
    informacao y = {31, 1.80, "Wilson"}; // Ajustado para bater com a struct informacao
    
    void *ptr; // Declaração de um ponteiro genérico (void)
    
    ptr = &a; // Atribuindo o endereço de um inteiro
    printf("a = %d \n", *((int*) ptr));
    
    ptr = &b; // Corrigido: na lista estava r=&b
    printf("b = %f \n", *((float*) ptr));
    
    ptr = &y; // Apontando para a struct
    // Corrigido: typecast correto para (informacao*) e acessando 'inteiro' (na lista estava 'idade')
    printf("nome=%s, inteiro = %i \n\n", ((informacao*) ptr)->nome, ((informacao*) ptr)->inteiro); 

    printf("\n\nAcessando um vetor por aritmetica de ponteiro void\n");
    ptr = &vet[0];
    
    // A CORREÇÃO PRINCIPAL: 
    // Em vez de fazer ptr++, nós convertemos temporariamente o (ptr) para um ponteiro de inteiro (int *)
    // antes de extrair o valor, e fazemos a matemática de andar as casas somando 'i' (ptr + i)
    for (int i = 0; i < 5; i++) { // Corrigido o limite para 5, já que o vetor só tem 5 posições
        printf("vet[%i] = %i \n", i, *((int*)ptr + i));
    }

    return 0;
}