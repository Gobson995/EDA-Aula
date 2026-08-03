#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dado;
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

int vazia(Pilha *p) {
    return (p->topo == NULL);
}

void empilha (Pilha *p, int valor) {
    No *novo = (No *) malloc (sizeof(No));

    if (novo == NULL) return;

    novo->dado = valor;
    novo->abaixo = p->topo;
    p->topo = novo;
}

void desempilha(Pilha *p) {
    if (vazia(p)) return;

    No *aux = p->topo;
    p->topo = aux->abaixo;
    free(aux);
}

int busca(Pilha *p) {
    if (vazia(p)) return -1;

    int valor_topo = p->topo->dado;

    return valor_topo;
}

void reinicia(Pilha *p) {
    while (p->topo != NULL) {
        desempilha(p);
    }
}

void destroi (Pilha *p) {
    reinicia(p);
    free(p);
}


