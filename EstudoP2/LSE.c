#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} info;

typedef struct no {
    info dados;
    struct no *prox;
} No;

typedef struct lse {
    int tamanho;
    int tamInfo;
    No *inicio;
} LSE;


LSE* cria(int tamInfo) {
    LSE *l = (LSE *) malloc(sizeof(LSE));

    if (l != NULL) {
        l->tamanho = 0;
        l->tamInfo = tamInfo;
        l->inicio = NULL;
    }

    return l;
}

int tamanhoDaLista (LSE *l) {
    if (l == NULL) return -1;
    return l->tamanho;
}

int testeVazia(LSE *l) {
    if (l == NULL) return -1;
    return (l->tamanho == 0);
}


int insereNaPosLog (LSE *l, int posLog, info *valor) {
    if (l == NULL || posLog < 0 || posLog > l->tamanho) return 0;

    No *novo = (No *) malloc (sizeof(No));
    if (novo == NULL) return 0;

    novo->dados = *valor;

    if (posLog == 0) {
        novo->prox = l->inicio;
        l->inicio = novo; 
    }
    else {
        No *atual = l->inicio;

        for (int i = 0; i < posLog - 1; i++) {
            atual = atual->prox;
        }

        novo->prox = atual->prox;
        atual->prox = novo;
    }

    l->tamanho++;

    return 1;
}

int insereNovoPrimeiro (LSE *l, info *valor) {
    return insereNaPosLog(l, 0, valor);
}

int insereNovoUltimo (LSE *l, info *valor) {
    return insereNaPosLog(l, l->tamanho, valor);
}


int buscaNaPosLog(LSE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    No *atual  = l->inicio;
    for (int i = 0; i < posLog; i++) {
        atual = atual->prox;
    }

    *valor = atual->dados;

    return 1;
}

int buscaOprimeiro(LSE *l, info *valor) {
    return buscaNaPosLog(l, 0, valor);
}

int buscaOultimo(LSE *l, info *valor) {
    return buscaNaPosLog(l, l->tamanho - 1, valor);
}


int removeDaPosLog(LSE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    No *velho;

    if (posLog == 0) {
        velho = l->inicio;
        *valor = velho->dados;
        l->inicio = velho->prox;
    }
    else {
        No *atual = l->inicio;
        
        for (int i = 0; i < posLog - 1; i++) {
            atual = atual->prox;
        }

        velho = atual->prox;
        *valor = velho->dados;

        atual->prox = velho->prox;
    }

    free(velho);
    l->tamanho--;

    return 1;
}

int removeOprimeiro(LSE *l, info *valor) {
    return removeDaPosLog(l, 0, valor);
}

int removeOultimo(LSE *l, info *valor) {
    return removeDaPosLog(l, l->tamanho - 1, valor);
}

int reinicia (LSE *l) {
    if (l == NULL) return 0;

    info lixo;

    while (!testeVazia(l)) {
        removeOprimeiro(l, &lixo);
    }

    return 1;
}

void destroi (LSE *l) {
    if (l != NULL) {
        reinicia(l);
        free(l);
    }
}


int inverte (LSE *l) {
    if (l == NULL || l->tamanho <= 1) return 1;

    No *ant = NULL;
    No *atual = l->inicio;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = ant;

        ant = atual;
        atual = proximo;
    }

    l->inicio = ant;

    return 1;
}