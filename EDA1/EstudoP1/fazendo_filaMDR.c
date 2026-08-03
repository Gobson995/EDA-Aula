#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct info {
    int dado;
} Info;

typedef struct mdr {
    Info vetor[MAX];
    int fim;
    int quantidade;
} MDR;

MDR* cria() {
    MDR *f = (MDR *) malloc (sizeof(MDR));
    if (f != NULL) {
        f->fim = -1;
        f->quantidade = 0;
    }

    return f;
}

int vazia (MDR *f) {
    return (f->quantidade == 0);
}

int cheia (MDR *f) {
    return (f->fim == MAX - 1);
}

int tamanhoFila (MDR *f) {
    return f->quantidade;
}

int reinicia (MDR *f) {
    f->fim = -1;
    f->quantidade = 0;
    return 1;
}

void destroi (MDR *f) {
    free(f);
}

int insere (MDR *f, Info valor) {
    if (cheia(f)) return 0;

    f->fim++;
    f->vetor[f->fim] = valor;
    f->quantidade++;

    return 1;
}

int buscaFrente (MDR *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[0];

    return 1;
}

int buscaCauda (MDR *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->fim];

    return 1;
}

int remove_ (MDR *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[0];

    for (int i = 0; i < f->fim; i++) {
        f->vetor[i] = f->vetor[i + 1];
    }

    f->fim--;
    f->quantidade--;

    return 1;
}

int inverte (MDR *f) {
    if (vazia(f) || f->quantidade == 1) return 1;

    int esq = 0;;
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

