#ifndef ARQPSE_H
#define ARQPSE_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura para guardar as coordenadas (x, y) de um pixel
typedef struct {
    int x;
    int y;
} info;

// Nó da pilha (lista encadeada)
struct Node{
    info dados;
    struct Node *under; // Ponteiro para o elemento "de baixo"
};

// Estrutura principal ("Descritor" da Pilha)
struct stack{
    struct Node *top; // Topo da pilha
    int stackSize;    // Contador de elementos
};

// Protótipos
int vazia(struct stack *stk);
struct stack *cria();
int insert(info *reg, struct stack *stk); // Equivale a push
int pop(struct stack *stk);
info first(struct stack *stk);            // Equivale a top/peek
void reset(struct stack *stk);
struct stack *destroy(struct stack *stk);

#endif