#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} info;

typedef struct no {
    info dados;
    int ocupado;
} No;

typedef struct abbest {
    int tamanho;
    int maxVetor;
    int tamInfo;
    No *nos;
} ABBEST;

ABBEST* cria(int maxVetor, int tamInfo) {
    ABBEST *arv = (ABBEST *) malloc(sizeof(ABBEST));

    if (arv != NULL) {
        arv->nos = (No *) malloc(maxVetor * sizeof(No));

        if (arv->nos == NULL) {
            free(arv);
            return NULL;
        }

        arv->tamanho = 0;
        arv->maxVetor = maxVetor;
        arv->tamInfo = tamInfo;

        for (int i = 0; i < maxVetor; i++) {
            arv->nos[i].ocupado = 0;
        }
    }

    return arv;
}

int testeVazia(ABBEST *arv) {
    if (arv == NULL) return -1;
    return (arv->tamanho == 0);
}

int insere(ABBEST *arv, info *valor) {
    if (arv == NULL) return 0;

    int i = 0;

    while (i < arv->maxVetor && arv->nos[i].ocupado != 0) {
        if (arv->nos[i].ocupado == 1 && valor->valor == arv->nos[i].dados.valor) {
            return 0;
        }

        if (valor->valor < arv->nos[i].dados.valor) {
            i = (2 * i) + 1;
        }
        else {
            i = (2 * i) + 2;
        }
    }

    if (i >= arv->maxVetor) return 0;

    arv->nos[i].dados = *valor;
    arv->nos[i].ocupado = 1;
    arv->tamanho++;

    return 1;
}

int busca (ABBEST *arv, int valorBuscado, info *resultado) {
    if (arv == NULL || testeVazia(arv)) return 0;

    int i = 0;

    while (i < arv->maxVetor && arv->nos[i].ocupado != 0) {
        if (arv->nos[i].ocupado == 1 && valorBuscado == arv->nos[i].dados.valor) {
            *resultado = arv->nos[i].dados;
            return 1; 
        }

        if (valorBuscado < arv->nos[i].dados.valor) {
            i = (2 * i) + 1;
        } else {
            i = (2 * i) + 2;
        }
    }

    return 0;
}

int remove_ (ABBEST *arv, int valorBuscado, info *resultado) {
    if (arv == NULL || testeVazia(arv)) return 0;

    int i = 0;

    while (i < arv->maxVetor && arv->nos[i].ocupado != 0) {
        if (arv->nos[i].ocupado == 1 && valorBuscado == arv->nos[i].dados.valor) {
            
            *resultado = arv->nos[i].dados;
            arv->nos[i].ocupado = -1; 
            arv->tamanho--;
            
            return 1;
        }

        if (valorBuscado < arv->nos[i].dados.valor) {
            i = (2 * i) + 1;
        } else {
            i = (2 * i) + 2;
        }
    }

    return 0;
}