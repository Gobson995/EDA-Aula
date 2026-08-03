#include <stdio.h>
#include <stdlib.h>

#define M 100

typedef struct mpe {
    int vetor[M];
    int topo1;
    int topo2;
    int tam_pilha1;
    int tam_pilha2;
} MPE;

MPE* cria() {
    MPE *p = (MPE *) malloc (sizeof (MPE));

    if (p != NULL) {
        p->tam_pilha1 = 0;
        p->tam_pilha2 = 0;
        p->topo1 = -1;
        p->topo2 = M;
    }
    return p;
}

int cheia (MPE *p) {
    return ((p->topo1 + 1) == p->topo2);
}

int vazia_esquerda (MPE *p) {
    return (p->topo1 == -1);
}

int vazia_direita (MPE *p) {
    return (p->topo2 == M);
}

int quantidade_esquerda (MPE *p) {
    return p->tam_pilha1;
}

int quantidade_direita (MPE *p) {
    return p->tam_pilha2;
}

int empilha_esquerda (MPE *p, int valor) {
    if (cheia(p)) return 0;

    p->topo1++;
    p->tam_pilha1++;
    p->vetor[p->topo1] = valor;

    return 1;
}

int empilha_direita (MPE *p, int valor) {
    if (cheia(p)) return 0;

    p->topo2--;
    p->tam_pilha2++;
    p->vetor[p->topo2] = valor;

    return 1;
}

int desempilha_esquerda (MPE *p) {
    if (vazia_esquerda(p)) return 0;

    p->topo1--;
    p->tam_pilha1--;

    return 1;
}

int desempilha_direita (MPE *p) {
    if (vazia_direita(p)) return 0;

    p->topo2++;
    p->tam_pilha2--;

    return 1;
}

int busca_esquerda (MPE *p, int *saida) {
    if (vazia_esquerda(p)) return 0;

    *saida = p->vetor[p->topo1];

    return 1;
}

int busca_direita (MPE *p, int *saida) {
    if (vazia_direita(p)) return 0;

    *saida = p->vetor[p->topo2];

    return 1;
}

void reinicia (MPE *p) {
    p->tam_pilha1 = 0;
    p->tam_pilha2 = 0;
    p->topo1 = -1;
    p->topo2 = M;
}

void destroi (MPE *p) {
    free(p);
}



