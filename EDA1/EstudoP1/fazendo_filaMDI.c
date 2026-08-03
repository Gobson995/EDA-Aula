#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct info {
    int valor;
} Info;

typedef struct mdi {
    Info vetor[MAX];
    int quantidade;
} MDI;

MDI* cria() {
    MDI *f = (MDI *) malloc (sizeof(MDI));

    if (f != NULL) {
        f->quantidade = 0;
    }

    return f;
}

int vazia (MDI *f) {
    return (f->quantidade == 0);
}

int cheia (MDI *f) {
    return (f->quantidade == MAX);
}

int insere (MDI *f, Info valor) {
    if (cheia(f)) return 0;

    

    for (int i = f->quantidade; i > 0; i--) {
        f->vetor[i] = f->vetor[i - 1];
    }

    f->vetor[0] = valor;
    f->quantidade++;

    return 1;
}

int tamanhoFila (MDI *f) {
    return f->quantidade;
}

int reinicia (MDI *f) {
    f->quantidade = 0;
    return 1;
}

void destroi (MDI *f) {
    free(f);
}

int buscaCauda (MDI *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[0];

    return 1;
}

int buscaFrente (MDI *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->quantidade - 1];

    return 1;
}

int remove_ (MDI *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->quantidade - 1];

    f->quantidade--;

    return 1;
}

int inverte (MDI *f) {
    if (f->quantidade == 0 || f->quantidade == 1) return 1;

    int esq = 0;
    int dir = f->quantidade-1;
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