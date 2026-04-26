#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dado;
    struct nodo *acima;
    struct nodo *abaixo;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

Pilha* cria() {
    Pilha *p = (Pilha *) malloc (sizeof(Pilha));

    if (p != NULL) {
        p->topo = NULL;
    }
    return p;
}

int vazia (Pilha *p) {
    return (p->topo == NULL);
}

void empilha (Pilha *p, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) return;

    novo->dado = valor;
    novo->acima = NULL;
    novo->abaixo = p->topo;
    
    if (p->topo != NULL) {
        p->topo->acima = novo;
    } 

    p->topo = novo;
}

void desempilha(Pilha *p) {
    if (vazia(p)) return;

    No *aux = p->topo;

    p->topo = aux->abaixo;

    if (p->topo != NULL) {
        p->topo->acima = NULL;
    }

    free(aux);
}

int busca (Pilha *p) {
    if (vazia(p)) return -1;
    return p->topo->dado;
}

void reinicia (Pilha *p) {
    while (p->topo != NULL) {
        desempilha(p);
    }
}

void destroi (Pilha *p) {
    reinicia(p);
    free(p);
}