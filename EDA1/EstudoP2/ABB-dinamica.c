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
    NoArv *raiz; // inicio = raiz
} ABB;


ABB* cria(int tamInfo) {
    ABB *arv = (ABB *) malloc(sizeof(ABB));
    if (arv != NULL) {
        arv->tamanho = 0;
        arv->tamInfo = tamInfo;
        arv->raiz = NULL; // A árvore nasce vazia
    }
    return arv;
}

int testeVazia(ABB *arv) {
    if (arv == NULL) return -1;
    return (arv->raiz == NULL);
}


int insere(ABB *arv, info *valor) {
    if (arv == NULL) return 0;

    NoArv *novo = (NoArv *) malloc(sizeof(NoArv));
    if (novo == NULL) return 0;

    novo->dados = *valor;
    novo->esq = NULL;
    novo->dir = NULL;

    // vazia, vira raiz
    if (arv->raiz == NULL) {
        arv->raiz = novo;
        arv->tamanho++;
        return 1;
    }

    // ja tem nós
    NoArv *atual = arv->raiz;
    NoArv *pai = NULL; // lembrar quem é o pai para fazer a ligação

    while (atual != NULL) {
        pai = atual;

        if (valor->valor == atual->dados.valor) { // valor repetido
            free(novo);
            return 0;
        }

        if (valor->valor < atual->dados.valor) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    if (valor->valor < pai->dados.valor) {
        pai->esq = novo;
    }
    else {
        pai->dir = novo;
    }

    arv->tamanho++;

    return 1;
}


int busca (ABB *arv,int valorBuscado, info *resultado) {
    if (arv == NULL || testeVazia(arv)) return 0;

    NoArv *atual = arv->raiz;

    while (atual != NULL) {
        if (valorBuscado == atual->dados.valor) {
            *resultado = atual->dados;
            return 1;
        }

        if (valorBuscado < atual->dados.valor) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    return 0;
}


int remove_ (ABB *arv, int valorBuscado, info *resultado) {
    if (arv == NULL || testeVazia(arv)) return 0;

    NoArv *atual = arv->raiz;
    NoArv *pai = NULL;

    // Busca o nó a ser removido
    while (atual != NULL && atual->dados.valor != valorBuscado) {
        pai = atual;
        if (valorBuscado < atual->dados.valor) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (atual == NULL) return 0; // Não achou

    *resultado = atual->dados;

    // CASO 3: Tem dois filhos
    if (atual->esq != NULL && atual->dir != NULL) {
        NoArv *subPai = atual;
        NoArv *substituto = atual->esq; // Ajustado o nome para 'substituto'

        // CORRIGIDO: 'while' escrito corretamente
        while (substituto->dir != NULL) {
            subPai = substituto;
            substituto = substituto->dir;
        }

        atual->dados = substituto->dados;

        atual = substituto;
        pai = subPai;
    }

    // CASOS 1 e 2: Tem 0 ou 1 filho
    NoArv *filho;
    if (atual->esq != NULL) {
        filho = atual->esq;
    } else {
        filho = atual->dir;
    }

    // Refaz as ligações
    if  (pai == NULL) {
        arv->raiz = filho;
    }
    else if (pai->esq == atual) {
        pai->esq = filho;
    }
    else {
        pai->dir = filho;
    }

    free(atual);
    arv->tamanho--;

    return 1;
}

