#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct fc {
    Info *vetor;
    int inicio;
    int fim;
    int quantidade;
    int tam_max;
} FC;

FC* cria (int tam_max) {
    FC *f = (FC *) malloc(sizeof(FC));
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

int vazia (FC *f) {
    return (f->quantidade == 0);
}

int cheia (FC *f) {
    return (f->quantidade == f->tam_max);
}

int insere (FC *f, Info valor) {
    if (cheia(f)) return 0;

    f->fim = (f->fim + 1) % f->tam_max;

    f->vetor[f->fim] = valor;
    f->quantidade++;

    return 1;
}
 
int remove_ (FC *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida  = f->vetor[f->inicio];

    f->inicio =  (f->inicio + 1) %  f->tam_max;
    f->quantidade--;

    return 1;
} 

int buscaNaFrente(FC *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->vetor[f->inicio];

    return 1;
}

int tamanho (FC *f) {
    return f->quantidade;
}

void reinicia(FC *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
}

void destroi (FC *f) {
    free(f->vetor);
    free(f);
}

int inverte (FC *f) {
    if (vazia(f) || f->quantidade == 1) return 1;

    int esq = f->inicio;
    int dir = f->fim;
    Info aux;

    for (int i = 0; i < (f->quantidade / 2); i++) {
        aux = f->vetor[esq];
        f->vetor[esq] = f->vetor[dir];
        f->vetor[dir] = aux;

        esq = (esq + 1) % f->tam_max;
        dir = (dir - 1 + f->tam_max) % f->tam_max;
    }

    return 1;
}
