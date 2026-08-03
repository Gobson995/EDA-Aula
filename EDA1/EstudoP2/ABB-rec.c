#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} info;

typedef struct noArv {
    info dados;
    struct noArv *esq;
    struct noArv *dir;
} NoArv;

typedef struct abb {
    int tamanho;
    int tamInfo;
    NoArv *raiz; 
} ABB;


ABB* cria(int tamInfo) {
    ABB *arv = (ABB *) malloc(sizeof(ABB));
    if (arv != NULL) {
        arv->tamanho = 0;
        arv->tamInfo = tamInfo;
        arv->raiz = NULL; 
    }
    return arv;
}

int testeVazia(ABB *arv) {
    if (arv == NULL) return -1;
    return (arv->raiz == NULL);
}


NoArv* insereRec (NoArv *no, info *valor, int *sucesso) {
    if (no == NULL) {
        NoArv *novo = (NoArv *) malloc(sizeof(NoArv));
        if (novo != NULL) {
            novo->dados = *valor;
            novo->esq = NULL;
            novo->dir = NULL;
            *sucesso = 1;
        }
        else {
            *sucesso = 0;
        }
        return novo;
    }

    if (valor->valor == no->dados.valor) {
        *sucesso = 0;
    }
    else if (valor->valor < no->dados.valor) {
        no->esq = insereRec(no->esq, valor, sucesso);
    }
    else {
        no->dir = insereRec(no->dir, valor, sucesso);
    }

    return no;
}

int insere (ABB *arv, info *valor) {
    if (arv == NULL) return 0;

    int sucesso = 0;
    arv->raiz = insereRec(arv->raiz, valor, &sucesso);

    if (sucesso) arv->tamanho++;
    return sucesso;
}


int buscaRec (NoArv *no, int valorBuscado, info *resultado) {
    if (no == NULL) return 0;

    if (valorBuscado == no->dados.valor) {
        *resultado = no->dados;
        return 1;
    }

    if (valorBuscado < no->dados.valor) {
        return buscaRec(no->esq, valorBuscado, resultado);
    }
    else {
        return buscaRec(no->dir, valorBuscado, resultado);
    }
}

int busca (ABB *arv, int valorBuscado, info *resultado) {
    if (arv == NULL || testeVazia(arv)) return 0;
    return buscaRec(arv->raiz, valorBuscado, resultado);
}


NoArv* removeRec(NoArv *no, int valorBuscado, info *resultado, int *sucesso) {
    if (no == NULL) {
        *sucesso = 0;
        return NULL;
    }

    if (valorBuscado < no->dados.valor) {
        no->esq = removeRec(no->esq, valorBuscado, resultado, sucesso);
    }
    else if (valorBuscado > no->dados.valor) {
        no->dir = removeRec(no->dir, valorBuscado, resultado, sucesso);
    }
    else {
        *resultado = no->dados;
        *sucesso = 1;

        if (no->esq == NULL) {
            NoArv *temp = no->dir;
            free(no);
            return temp;
        }
        else if (no->dir == NULL) {
            NoArv *temp = no->esq;
            free(no);
            return temp;
        }
        else {
            NoArv *temp = no->esq;
            while (temp->dir != NULL) {
                temp = temp->dir;
            }
            
            no->dados = temp->dados;
            
            int lixoSucesso;
            info lixoInfo;
            no->esq = removeRec(no->esq, temp->dados.valor, &lixoInfo, &lixoSucesso);
        }
    }
    return no;
}

int remove_ (ABB *arv, int valorBuscado, info *resultado) {
    if (arv == NULL || testeVazia(arv)) return 0;
    
    int sucesso = 0;
    arv->raiz = removeRec(arv->raiz, valorBuscado, resultado, &sucesso);
    
    if (sucesso) arv->tamanho--;
    return sucesso;
}