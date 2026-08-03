#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct info {
    int valor;
} Info;

typedef struct fes {
    Info vetor[MAX];
    int inicio;
    int fim;
    int quantidade;
} FES;

FES* cria() {
    FES *f = (FES *) malloc (sizeof(FES));

    if (f != NULL) {
        f->inicio = 0;
        f->fim = -1;
        f->quantidade = 0;
    }

    return f;
}

int vazia (FES *f) {
    return (f->quantidade == 0);
}

int cheia (FES *f) {
    return (f->fim == MAX - 1);
}

int enfileirar (FES *f, Info dado) {
    if (cheia(f)) return 0;

    f->fim++;
    f->vetor[f->fim] = dado;
    f->quantidade++;

    return 1;
}

int desenfileirar (FES *f, Info *saida) {
    if (vazia(f)) return 0;
    
    *saida = f->vetor[f->inicio];

    f->inicio++;
    f->quantidade--;

    return 1;
}

void destroi (FES *f) {
    free(f);
}

int tamanhoDaFila (FES *f) {
    return f->quantidade;
}

int reinicia (FES *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;

    return 1;
} 

int buscaNaFrente (FES *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->inicio];

    return 1;
}

int buscaNaCauda(FES *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->fim];

    return 1;
}

int inverte (FES *f) {
    if (vazia(f) || f->quantidade == 1) return 1;

    int esq = f->inicio;
    int dir = f->fim;
    Info temp;

    while (esq < dir) {
        temp = f->vetor[esq];

        f->vetor[esq] = f->vetor[dir];

        f->vetor[dir] = temp;

        esq++;
        dir--;
    }

    return 1;
}