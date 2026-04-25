#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dado;
    struct nodo *abaixo;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

void push(Pilha *p, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo != NULL) {
        novo->dado = valor;

        novo->abaixo = p->topo;
        p->topo = novo;

        printf("Empilhado com sucesso!\n");
    }
    else {
        printf("Erro: Memoria cheia!\n");
    }
}

void pop(Pilha *p) {
    if (p != NULL && p->topo != NULL) {
        No *aux = p->topo;
        p->topo = aux->abaixo;

        free(aux);

        printf("Desempilhado com sucesso!\n");
    }
    else {
        printf("Nao tem nada, ou seja, nao tem como remover");
    }
}

// bonus:
void imprimir_pilha(Pilha *p) {
    printf("\n--- Estado Atual da Pilha ---\n");

    if (p->topo == NULL) {
        printf("A pilha esta vazia!\n");
        printf("-----------------------------\n");
        return;
    }

    No *atual = p->topo;

    while (atual != NULL) {
        printf("%d\n", atual->dado);

        atual = atual->abaixo;
    }

    printf("-----------------------------\n");
}

int limpar_pilha (Pilha *p) {
    int contador = 0;

    while (p->topo != NULL) {
        pop(p);
        contador++;
    }

    return contador;
}

int main () {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));

    if (p != NULL) {
        p->topo = NULL;

        push(p, 10);
        push(p, 20);
        push(p, 83);
        push(p, 13);

        // bonus:
        imprimir_pilha(p);

        int resposta = limpar_pilha(p);

        printf("Tinha %d caixa na sua pilha, agora ela esta vazia!\n", resposta);
    }
    else {
        printf("Erro critico: Falha ao alocar memoria!\n");
        return 1;
    }
    
    return 0;
}