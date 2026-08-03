#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct nodo {
    Info dado;
    struct nodo *abaixo;
} No;

typedef struct pse {
    No *topo;
} PSE;

PSE* cria() {
    PSE *p = (PSE*) malloc(sizeof(PSE));

    if (p != NULL) {
        p->topo = NULL;
    }

    return p;
}

int vazia(PSE *p) {
    return (p->topo == NULL);
}

int empilha(PSE *p, Info valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo != NULL) {
        novo->abaixo = p->topo;
        novo->dado = valor;
        p->topo = novo;
        return 1;
    }
    else return 0;
}

int desempilha (PSE *p, Info *saida) {
    if (vazia(p)) return 0;

    No *aux = p->topo;

    *saida = p->topo->dado;
    
    p->topo = aux->abaixo;
    free(aux);

    return 1;
}

int buscaNoTopo (PSE *p, Info *saida) {
    if (vazia(p)) return 0;

    *saida = p->topo->dado;

    return 1;
}

int buscaNaBase (PSE *p, Info *saida) {
    if (vazia(p)) return 0;

    No *aux = p->topo;

    while (aux->abaixo != NULL) {
        aux = aux->abaixo;
    }

    *saida = aux->dado;

    return 1;
}

int tamanho (PSE *p) {
    if (vazia(p)) return 0; 
    
    int contador = 0;

    No *aux = p->topo;

    while (aux != NULL) {
        aux = aux->abaixo;
        contador++;
    }

    return contador;
}

void reinicia (PSE *p) {
    No *aux1 = p->topo;
    No *aux2 = NULL;

    while (aux1 != NULL) {
        aux2 = aux1->abaixo;
        free(aux1);
        aux1 = aux2;
    }

    p->topo = NULL;
}

void destroi (PSE *p) {
    reinicia(p);
    free(p);
}

int inverte (PSE *p) {
    if (vazia(p) || p->topo->abaixo == NULL) return 1;

    No *anterior = NULL;
    No *atual = p->topo;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->abaixo;
        atual->abaixo = anterior;

        anterior = atual;
        atual = proximo;
    }

    p->topo = anterior;
}

