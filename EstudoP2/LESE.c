#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} info;

typedef struct no {
    info dados;
    int prox;
} No;

typedef struct lese {
    int tamanho;
    int maxVetor;
    int tamInfo;
    int inicio;
    int listDisp;
    No *nos;
} LESE;


int obtemNoh (LESE *l) {
    if (l->listDisp == -1) return -1;

    int indiceLivre = l->listDisp;
    l->listDisp = l->nos[indiceLivre].prox;

    return indiceLivre;
}

int devolveNoh (LESE *l, int pos) {
    if (pos < 0 || pos >= l->maxVetor) return 0;

    l->nos[pos].prox = l->listDisp;
    l->listDisp = pos;

    return 1;
}


LESE * cria(int tamanhoVetor, int tamInfo) {
    LESE *l = (LESE *) malloc (sizeof(LESE));
    
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
        l->listDisp = 0;

        for (int i = 0; i < tamanhoVetor - 1; i++) {
            l->nos[i].prox = i + 1;
        }

        l->nos[tamanhoVetor - 1].prox = -1;
    }

    return l;
}

int tamanhoDaLista(LESE *l) {
    if (l == NULL) return -1;
    return l->tamanho;
}

int testeVazia(LESE *l) {
    if (l == NULL) return -1;
    return (l->tamanho == 0);
}

int testeCheia(LESE *l) {
    if (l == NULL) return -1;
    return (l->listDisp == -1);
}


int insereNaPosLog (LESE *l, int posLog, info *valor) {
    if (l == NULL || posLog < 0 || posLog > l->tamanho || testeCheia(l)) return 0;

    int novo = obtemNoh(l);
    if (novo == -1) return 0;

    l->nos[novo].dados = *valor;

    if (posLog == 0) {
        l->nos[novo].prox = l->inicio;
        l->inicio = novo;
    }
    else {
        int atual = l->inicio;

        for (int i = 0; i < posLog - 1; i++) {
            atual = l->nos[atual].prox;
        }

        l->nos[novo].prox = l->nos[atual].prox;
        l->nos[atual].prox = novo;
    }

    l->tamanho++;
    return 1;
}

int insereNovoPrimeiro (LESE *l, info *valor) {
    return insereNaPosLog(l, 0, valor);
}

int insereNovoUltimo (LESE *l, info *valor) {
    return insereNaPosLog(l, l->tamanho, valor);
}


int buscaNaPosLog (LESE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    int atual = l->inicio;

    for (int i = 0; i < posLog; i++) {
        atual = l->nos[atual].prox;
    }

    *valor = l->nos[atual].dados;
    return 1;
}

int buscaOprimeiro(LESE *l, info *valor) {
    return buscaNaPosLog(l, 0, valor);
}

int buscaOultimo(LESE *l, info *valor) {
    return buscaNaPosLog(l, l->tamanho - 1, valor);
}


int removeDaPosLog (LESE *l, int posLog, info *valor) {
    if (l == NULL || testeVazia(l) || posLog < 0 || posLog >= l->tamanho) return 0;

    int velho;

    if (posLog == 0) {
        velho = l->inicio;
        *valor = l->nos[velho].dados;
        l->inicio = l->nos[velho].prox;
    }
    else {
        int atual = l->inicio;

        for (int i = 0; i < posLog - 1; i++) {
            atual = l->nos[atual].prox;
        }

        velho = l->nos[atual].prox;
        *valor = l->nos[velho].dados;
        l->nos[atual].prox = l->nos[velho].prox;
    }

    devolveNoh(l, velho);
    l->tamanho--;
    
    return 1;
}

int removeOprimeiro(LESE *l, info *valor) {
    return removeDaPosLog(l, 0, valor);
}

int removeOultimo(LESE *l, info *valor) {
    return removeDaPosLog(l, l->tamanho - 1, valor);
}


int reinicia(LESE *l) {
    if (l == NULL) return 0;

    info lixo;

    while (!testeVazia(l)) {
        removeOprimeiro(l, &lixo);
    }

    return 1;
}

LESE* destroi (LESE *l) {
    if (l != NULL) {
        free(l->nos); 
        free(l); 
    }

    return NULL;
}