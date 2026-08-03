#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct nodo {
    Info dado;
    struct nodo *abaixo;
    struct nodo *acima;
} No;

typedef struct pde {
    No *topo;
} PDE;

PDE* cria() {
    PDE *p = (PDE *) malloc(sizeof(PDE));

    if (p != NULL) {
        p->topo = NULL;
    }

    return p;
}

int vazia(PDE *p) {
    return (p->topo == NULL);
}

int empilha (PDE *p, Info valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo != NULL) {
        novo->abaixo = p->topo;
        novo->acima = NULL;
        novo->dado = valor;

        if (p->topo != NULL) {
            p->topo->acima = novo;
        }

        p->topo = novo;

        return 1;
    }

    return 0;
}

int desempilha (PDE *p, Info *saida) {
    if (vazia(p)) return 0;

    *saida = p->topo->dado;

    No *aux = p->topo;

    p->topo = aux->abaixo;

    if (p->topo != NULL) {
        p->topo->acima = NULL;
    }
   
    free(aux);

    return 1;
}

int buscaNoTopo (PDE *p, Info *saida) {
    if (vazia(p)) return 0;

    *saida = p->topo->dado;

    return 1;
}

int buscaNaBase (PDE *p, Info *saida) {
    if (vazia(p)) return 0;

    No *aux = p->topo;

    while (aux->abaixo != NULL) {
        aux = aux->abaixo;
    }

    *saida = aux->dado;

    return 1;
}

int tamanho (PDE *p) {
    int contador = 0;

    No *aux = p->topo;

    while (aux != NULL) {
        aux = aux->abaixo;
        contador++;
    }

    return contador;
}

void reinicia (PDE *p) {
    No *aux1 = p->topo;
    No *aux2;

    while (aux1 != NULL) {
        aux2 = aux1->abaixo;
        free(aux1);
        aux1 = aux2;
    }

    p->topo = NULL;
}

void destroi (PDE *p) {
    reinicia(p);
    free(p);
}

int inverte (PDE *p) {
    if (vazia(p) || p->topo->abaixo == NULL) return 1;

    No *atual = p->topo;
    No *aux = NULL;

    while (atual != NULL) {
        aux = atual->abaixo;
        atual->abaixo = atual->acima;
        atual->acima = aux;
        
        if (atual->acima == NULL) {
            p->topo = atual;
        }

        atual = atual->acima;
    }

    return 1;
}
