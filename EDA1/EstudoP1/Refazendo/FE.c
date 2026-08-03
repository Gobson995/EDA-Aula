#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct fe {
    Info *vetor;
    int inicio;
    int fim;
    int quantidade;
    int tam_max;
} FE;

FE* cria(int tam_max) {
    FE *f = (FE *) malloc(sizeof(FE));
    Info *vetor = (Info *) malloc(sizeof(Info) * tam_max);

    if (f != NULL) {
        f->vetor = vetor;
        f->inicio = 0;
        f->fim = -1;
        f->quantidade = 0;
        f->tam_max = tam_max;
    }

    return f;
}

int cheia(FE *f) {
    return (f->fim + 1 == f->tam_max);
}

int vazia(FE *f) {
    return (f->quantidade == 0);
}

int insere (FE *f, Info valor) {
    if (cheia(f)) return 0;

    f->fim++;
    f->vetor[f->fim] = valor;
    f->quantidade++;

    return 1;
}

int remove_ (FE *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->inicio];

    f->inicio++;
    f->quantidade--;

    return 1;
}

int buscaNaFrente(FE *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->inicio];

    return 1;
}

int tamanho (FE *f) {
    return f->quantidade;
}

void reinicia(FE *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
}

void destroi (FE *f) {
    free(f->vetor);
    free(f);
}

