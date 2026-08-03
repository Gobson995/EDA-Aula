#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arqPSE.h"

// Verifica se a pilha não existe ou se o tamanho é zero
int vazia(struct stack *stk){
    return (stk == NULL || stk->stackSize == 0);
}

// Aloca memória para a estrutura da pilha e zera os ponteiros
struct stack *cria(){
    struct stack *stk = malloc(sizeof(struct stack));
    
    if(stk){
        stk->top = NULL;
        stk->stackSize = 0;
    }
    return stk;
}

// Empilha (Push): Cria um nó novo, guarda o dado e o coloca no topo
int insert(info *reg, struct stack *stk){
    if(stk == NULL) return 0;

    struct Node *aux = malloc(sizeof(struct Node));

    if(aux != NULL){
        memcpy(&(aux->dados), reg, sizeof(info)); 
        aux->under = stk->top; // Novo nó segura o antigo topo
        stk->top = aux;        // A pilha aponta para o novo topo
        (stk->stackSize)++;
        return 1;
    }
    return 0;
}

// Desempilha (Pop): Remove o elemento do topo e liga a pilha no de baixo
int pop(struct stack *stk){
    if(!vazia(stk)){
        struct Node *aux = stk->top->under; // Salva o endereço do cara de baixo
        free(stk->top);                     // Destrói a "caixa" do topo
        stk->top = aux;                     // O de baixo vira o novo topo
        (stk->stackSize)--;
        return 1;
    }
    return 0;
}

// Apenas "olha" quem está no topo sem remover
info first(struct stack *stk){
    if(vazia(stk)){
        info vazio = {-1, -1}; // Prevenção de erro
        return vazio;
    }
    return stk->top->dados;
}

// Desempilha tudo até esvaziar
void reset(struct stack *stk){
    while(pop(stk));
}

// Esvazia os nós e depois liberta o próprio descritor
struct stack *destroy(struct stack *stk){
    if(stk == NULL) return NULL;
    reset(stk);
    free(stk);
    return NULL;
}