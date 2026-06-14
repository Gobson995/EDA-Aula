#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} info;

typedef struct no {
    info dados;
    struct no *ant;
    struct no *prox;
} No;

typedef struct lde {
    int tamanho;
    int tamInfo;
    No *inicio;
    No *cauda;
    No *refMovel;
    int posRefMovel;
} LDE;


LDE* cria(int tamInfo) {
    LDE *l = (LDE *) malloc(sizeof(LDE));

    if (l != NULL) {
        l->tamanho = 0;
        l->tamInfo = tamInfo;
        l->inicio = NULL;
        l->cauda = NULL;
        l->refMovel = NULL;
        l->posRefMovel = -1;
    }

    return l;
}

int tamanhoDaLista (LDE *l) {
    if (l == NULL) return -1;
    return l->tamanho;
}

int testeVazia(LDE *l) {
    if (l == NULL) return -1;
    return (l->tamanho == 0);
}

No *navegar(LDE *l, int alvo) {
    if (alvo == 0) return l->inicio;
    if (alvo == l->tamanho - 1) return l->cauda;
    if (alvo == l->posRefMovel) return l->refMovel;

    No *atual = NULL;

    if (l->posRefMovel == -1) {
        atual = l->inicio;
        for (int i = 0; i < alvo; i++) atual = atual->prox;
    }
    else if (alvo < l->posRefMovel) {
        int distInicio = alvo;
        int distRef = l->posRefMovel - alvo;

        if (distInicio <= distRef) {
            atual = l->inicio;
            for (int i = 0; i < alvo; i++) atual = atual->prox;
        }
        else {
            atual = l->refMovel;
            for (int i = 0; i < distRef; i++) atual = atual->ant;
        }
    }
    else {
        int distRef = alvo - l->posRefMovel;
        int distFim = (l->tamanho - 1) - alvo;

        if (distRef <= distFim) {
            atual = l->refMovel;
            for (int i = 0; i < distRef; i++) atual = atual->prox;
        }
        else {
            atual = l->cauda;
            for (int i = 0; i < distFim; i++) atual = atual->ant;
        }
    }

    l->refMovel = atual;
    l->posRefMovel = alvo;

    return atual;
}


int insereNaPosLog (LDE *l, int posLog, info *valor) {
    if (l == NULL || posLog < 0 || posLog > l->tamanho) return 0;

    No *novo = (No *) malloc (sizeof(No));
    if (novo == NULL) return 0;

    novo->dados = *valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if (posLog == 0) {
        novo->prox = l->inicio;
        
        if (l->inicio != NULL) {
            l->inicio->ant = novo;
        }
        else {
            l->cauda = novo;
        }

        l->inicio = novo;
    }
    else if (posLog == l->tamanho) {
        novo->ant = l->cauda;
        l->cauda->prox = novo;
        l->cauda = novo;
    }
    else {
        No *atual = navegar(l, posLog);

        novo->prox = atual;
        novo->ant = atual->ant;

        atual->ant->prox = novo;
        atual->ant = novo;
    }

    l->tamanho++;

    l->refMovel = novo;
    l->posRefMovel = posLog;

    return 1;
}

int insereNovoPrimeiro (LDE *l, info *valor) {
    return insereNaPosLog(l, 0, valor);
}

int insereNovoUltimo (LDE *l, info *valor) {
    return insereNaPosLog(l, l->tamanho, valor);
}


int buscaNaPosLog(LDE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    No *alvo = navegar(l, posLog);
    *valor = alvo->dados;

    return 1;
}

int buscaOprimeiro(LDE *l, info *valor) {
    return buscaNaPosLog(l, 0, valor);
}

int buscaOultimo(LDE *l, info *valor) {
    return buscaNaPosLog(l, l->tamanho - 1, valor);
}


int removeDaPosLog(LDE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    No *velho;

    if (posLog == 0) {
        velho = l->inicio;
        *valor = velho->dados;
        l->inicio = velho->prox;

        if (l->inicio != NULL) {
            l->inicio->ant = NULL;
        }
        else {
            l->cauda = NULL;
        }
    }
    else if (posLog == l->tamanho - 1) {
        velho = l->cauda;
        *valor = velho->dados;
        l->cauda = velho->ant;
        l->cauda->prox = NULL;
    }
    else {
        velho = navegar(l, posLog);
        *valor = velho->dados;

        velho->ant->prox = velho->prox;
        velho->prox->ant = velho->ant;
    }

    if (velho->ant != NULL) {
        l->refMovel = velho->ant;
        l->posRefMovel = posLog - 1;
    } else if (l->inicio != NULL) { 
        l->refMovel = l->inicio;
        l->posRefMovel = 0;
    } else { 
        l->refMovel = NULL;
        l->posRefMovel = -1;
    }

    free(velho);
    l->tamanho--;

    return 1;
}

int removeOprimeiro(LDE *l, info *valor) {
    return removeDaPosLog(l, 0, valor);
}

int removeOultimo(LDE *l, info *valor) {
    return removeDaPosLog(l, l->tamanho - 1, valor);
}

int reinicia (LDE *l) {
    if (l == NULL) return 0;

    info lixo;

    while (!testeVazia(l)) {
        removeOprimeiro(l, &lixo);
    }

    return 1;
}

void destroi (LDE *l) {
    if (l != NULL) {
        reinicia(l);
        free(l);
    }
}


int inverte (LDE *l) {
    if (l == NULL || l->tamanho <= 1) return 1;

    No *atual = l->inicio;
    No *temp = NULL;

    while (atual != NULL) {
        temp = atual->ant;
        atual->ant = atual->prox;
        atual->prox = temp;

        atual = atual->ant;
    }

    temp = l->inicio;
    l->inicio = l->cauda;
    l->cauda = temp;

    l->refMovel = NULL;
    l->posRefMovel = -1;

    return 1;
}