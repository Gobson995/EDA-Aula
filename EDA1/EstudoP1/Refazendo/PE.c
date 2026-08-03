#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} Info;

typedef struct pe {
    Info *vetor;
    int topo;
    int tamanho;
    int tam_max;
} PE;

PE* cria(int tam_max) {
    PE *p = (PE *) malloc(sizeof(PE));
    Info *vetor = (Info *) malloc(sizeof(Info) * tam_max);

    if (p != NULL) {
        p->vetor = vetor;
        p->topo = -1;
        p->tamanho = 0;
        p->tam_max = tam_max;
    }

    return p;
}

int vazia(PE *p) {
    return (p->tamanho == 0);
}

int cheia(PE *p) {
    return (p->tamanho == p->tam_max);
}

int empilha(PE *p, Info valor) {
    if (cheia(p)) return 0;

    p->topo++;
    p->tamanho++;
    p->vetor[p->topo] = valor;

    return 1;
}

int desempilha(PE *p, Info *saida) {
    if (vazia(p)) return 0;

    *saida = p->vetor[p->topo];

    p->topo--;
    p->tamanho--;

    return 1;
}

int buscaNoTopo(PE *p, Info *saida) {
    if (vazia(p)) return 0;

    *saida = p->vetor[p->topo];

    return 1;
}

int buscaNoBase(PE *p, Info *saida) {
    if (vazia(p)) return 0;

    *saida = p->vetor[0];

    return 1;
}

int tamanho(PE *p) {
    return p->tamanho;
}

void reinicia (PE *p) {
    p->topo = -1;
    p->tamanho = 0;
}

void destroi(PE *p) {
    free(p->vetor);
    free(p);
}

int inverte (PE *p) {
    if (p->tamanho == 0 || p->tamanho == 1) return 1;

    int esq = 0;
    int dir = p->topo;
    Info aux;

    while (esq < dir) {
        aux = p->vetor[esq];
        p->vetor[esq] = p->vetor[dir];
        p->vetor[dir] = aux;

        esq++;
        dir--;
    }

    return 1;
}


