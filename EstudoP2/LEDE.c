#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} info;

typedef struct no {
    info dados;
    int ant;
    int prox;
} No;

typedef struct lede {
    int tamanho;
    int maxVetor;
    int tamInfo;
    int inicio;
    int cauda;
    int listDisp;
    No *nos;
} LEDE;


int obtemNoh (LEDE *l) {
    if (l->listDisp == -1) return -1;

    int indiceLivre = l->listDisp;
    l->listDisp = l->nos[indiceLivre].prox;

    return indiceLivre;
}

int devolveNoh (LEDE *l, int pos) {
    if (pos < 0 || pos >= l->maxVetor) return 0;

    l->nos[pos].prox = l->listDisp;
    l->listDisp = pos;

    return 1;
}


LEDE * cria(int tamanhoVetor, int tamInfo) {
    LEDE *l = (LEDE *) malloc (sizeof(LEDE));
    
    if (l != NULL) {
        l->nos = (No *) malloc (tamanhoVetor * sizeof(No));

        if (l->nos == NULL) {
            free(l);
            return NULL;
        }

        l->tamanho = 0;
        l->maxVetor = tamanhoVetor;
        l->tamInfo = tamInfo;
        l->inicio = -1;
        l->cauda = -1;
        l->listDisp = 0;

        for (int i = 0; i < tamanhoVetor - 1; i++) {
            l->nos[i].prox = i + 1;
        }

        l->nos[tamanhoVetor - 1].prox = -1;
    }

    return l;
}

int tamanhoDaLista(LEDE *l) {
    if (l == NULL) return -1;
    return l->tamanho;
}

int testeVazia(LEDE *l) {
    if (l == NULL) return -1;
    return (l->tamanho == 0);
}

int testeCheia(LEDE *l) {
    if (l == NULL) return -1;
    return (l->listDisp == -1);
}


int insereNaPosLog (LEDE *l, int posLog, info *valor) {
    if (l == NULL || posLog < 0 || posLog > l->tamanho || testeCheia(l)) return 0;

    int novo = obtemNoh(l);
    if (novo == -1) return 0;

    l->nos[novo].dados = *valor;
    l->nos[novo].prox = -1;
    l->nos[novo].ant = -1;

    if (posLog == 0) {
        l->nos[novo].prox = l->inicio;
        
        if (l->inicio != -1) {
            l->nos[l->inicio].ant = novo;
        }
        else {
            l->cauda = novo;
        }

        l->inicio = novo;
    }
    else if (posLog == l->tamanho) {
        l->nos[novo].ant = l->cauda;
        l->nos[l->cauda].prox = novo;
        l->cauda = novo;
    }
    else {
        int atual = l->inicio;

        for (int i = 0; i < posLog - 1; i++) {
            atual = l->nos[atual].prox;
        }

        l->nos[novo].prox = l->nos[atual].prox;
        l->nos[novo].ant = atual;

        l->nos[l->nos[atual].prox].ant = novo;
        l->nos[atual].prox = novo;
    }

    l->tamanho++;
    return 1;
}

int insereNovoPrimeiro (LEDE *l, info *valor) {
    return insereNaPosLog(l, 0, valor);
}

int insereNovoUltimo (LEDE *l, info *valor) {
    return insereNaPosLog(l, l->tamanho, valor);
}


int buscaNaPosLog (LEDE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    int atual = l->inicio;

    for (int i = 0; i < posLog; i++) {
        atual = l->nos[atual].prox;
    }

    *valor = l->nos[atual].dados;
    return 1;
}

int buscaOprimeiro(LEDE *l, info *valor) {
    return buscaNaPosLog(l, 0, valor);
}

int buscaOultimo(LEDE *l, info *valor) {
    return buscaNaPosLog(l, l->tamanho - 1, valor);
}


int removeDaPosLog (LEDE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    int velho;

    if (posLog == 0) {
        velho = l->inicio;
        *valor = l->nos[velho].dados;
        l->inicio = l->nos[velho].prox;

        if (l->inicio != -1) {
            l->nos[l->inicio].ant = -1;
        }
        else {
            l->cauda = -1;
        }
    }
    else if (posLog == l->tamanho -1) {
        velho = l->cauda;
        *valor = l->nos[velho].dados;
        l->cauda = l->nos[velho].ant;
        l->nos[l->cauda].prox = -1;
    }
    else {
        int atual = l->inicio;

        for (int i = 0; i < posLog - 1; i++) {
            atual = l->nos[atual].prox;
        }

        velho = l->nos[atual].prox;
        *valor = l->nos[velho].dados;

        l->nos[atual].prox = l->nos[velho].prox;
        l->nos[l->nos[velho].prox].ant = atual;
    }

    devolveNoh(l, velho);
    l->tamanho--;
    
    return 1;
}

int removeOprimeiro(LEDE *l, info *valor) {
    return removeDaPosLog(l, 0, valor);
}

int removeOultimo(LEDE *l, info *valor) {
    return removeDaPosLog(l, l->tamanho - 1, valor);
}


int reinicia(LEDE *l) {
    if (l == NULL) return 0;

    info lixo;

    while (!testeVazia(l)) {
        removeOprimeiro(l, &lixo);
    }

    return 1;
}

LEDE* destroi (LEDE *l) {
    if (l != NULL) {
        free(l->nos); 
        free(l); 
    }

    return NULL;
}