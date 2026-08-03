#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct info {
    int valor;
} Info;

typedef struct filacircular {
    Info vetor[MAX];
    int inicio;
    int fim;
    int quantidade;
} FC;

FC* cria() {
    FC *f = (FC *) malloc (sizeof(FC));

    if (f != NULL) {
        f->inicio = 0;
        f->fim = -1;
        f->quantidade = 0;
    }

    return f;
}

int vazia(FC *f) {
    return (f->quantidade == 0);
}

int cheia (FC *f) {
    return (f->quantidade == MAX);
}

int TamanhoFila (FC *f) {
    return f->quantidade;
}

int reinicia (FC *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
    return 1;
}

void destroi (FC *f) {
    free(f);
}

int insere (FC *f, Info valor) {
    if (cheia(f)) return 0;

    f->fim = (f->fim + 1) % MAX;

    f->vetor[f->fim] = valor;
    f->quantidade++;

    return 1;
}

int remove_ (FC *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->inicio];

    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;

    return 1;
}

int buscaCauda (FC *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->fim];

    return 1;
}

int buscaFrente (FC *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->inicio];

    return 1;
}

int inverte (FC *f) {
    if (vazia(f)) return 0;

    int esq = f->inicio;
    int dir = f->fim;
    Info temp;

    for (int i = 0; i < (f->quantidade / 2); i++) {
        temp = f->vetor[esq];
        f->vetor[esq] = f->vetor[dir];
        f->vetor[dir] = temp;

        esq = (esq + 1) % MAX;
        dir = (dir - 1 + MAX) % MAX;
    }

    return 1;
}