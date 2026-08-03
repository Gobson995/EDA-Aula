#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int prioridade;
} info;

typedef struct no {
    info dados;
    struct no *atras;
    struct no *defronte;
} No;

typedef struct fdemovel {
    int tamanho;
    No *frente;
    No *cauda;
    No *libero;
} FDEMOVEL;


FDEMOVEL* cria() {
    FDEMOVEL *p = (FDEMOVEL *) malloc(sizeof(FDEMOVEL));

    if (p != NULL) {
        p->tamanho = 0;
        p->frente = NULL;
        p->cauda = NULL;
        p->libero = NULL;
    }

    return p;
}

int insere (FDEMOVEL *p, info *dados) {
    No *novo = (No *) malloc (sizeof (No));
    if (novo == NULL) return 0;

    novo->dados = *dados;
    novo->defronte = NULL;
    novo->atras = NULL;

    if (p->tamanho == 0) {
        p->frente = novo;
        p->cauda = novo;
        p->libero = novo;
        p->tamanho++;
        return 1;
    }

    No *atual = p->libero;

    if (novo->dados.prioridade < atual->dados.prioridade) {
        while (atual != NULL && novo->dados.prioridade < atual->dados.prioridade) {
            atual = atual->atras;
        }

        if (atual == NULL) {
            novo->defronte = p->frente;
            p->frente->atras = novo;
            p->frente = novo;
        }
        else {
            novo->defronte = atual->defronte;
            novo->atras = atual;
            if (atual->defronte != NULL) {
                atual->defronte->atras = novo;
            }
            atual->defronte = novo;
        }
    }
    else {
        while (atual != NULL && novo->dados.prioridade >= atual->dados.prioridade) {
            atual = atual->defronte;
        }

        if (atual == NULL) {
            novo->atras = p->cauda;
            p->cauda->defronte = novo;
            p->cauda = novo;
        }
        else {
            novo->atras = atual->atras;
            novo->defronte = atual;
            if (atual->atras != NULL) {
                atual->atras->defronte = novo;
            }
            atual->atras = novo;
        }
    }

    p->libero = novo;
    p->tamanho++;

    return 1;
}

int remove_ (FDEMOVEL *p, info *dados) {
    if (p->tamanho == 0) return 0;

    No *velho = p->frente;
    *dados = velho->dados;

    p->frente = velho->defronte;

    if (p->frente == NULL) {
        p->cauda = NULL;
    }
    else {
        p->frente->atras = NULL;
    }

    free(velho);
    p->tamanho--;

    p->libero = p->frente;

    return 1;
}