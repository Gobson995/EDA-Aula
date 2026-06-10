#include "arq.h"

static void troca(info *a, info *b){
    info tmp = *a;
    *a = *b;
    *b = tmp;
}


struct fila * cria(int tamInfo, Comparador compara) {

    struct fila *fila = malloc(sizeof(struct fila));
    if(!fila) return NULL;

    fila->heap = malloc(CAP_INICIAL * sizeof(info));
    if(!fila->heap){
        free(fila);
        return NULL;
    }

    fila->capacidade = CAP_INICIAL;
    fila->tamanho = 0;
    fila->tamInfo = tamInfo;
    fila->itersInseracao = 0;
    fila->compara = compara;

    return fila;
}


int insere(info *novo, struct fila *fila) {
    if (!fila || !novo) return 0;
 
    if (fila->tamanho == fila->capacidade) {
        int novaCap = fila->capacidade * 2;
        info *tmp = realloc(fila->heap, novaCap * sizeof(info));
        if (!tmp) return 0;
        fila->heap = tmp;
        fila->capacidade = novaCap;
    }
 
    int pos = fila->tamanho;
    fila->heap[pos] = *novo;
    fila->tamanho++;
    fila->itersInseracao = 0;
 
    int pai = (pos - 1) / 2;
    while (pos > 0 && fila->compara(&fila->heap[pos], &fila->heap[pai])) {
        fila->itersInseracao++;
        troca(&fila->heap[pos], &fila->heap[pai]);
        pos = pai;
        pai = (pos - 1) / 2;
    }
 
    return 1;
}


int remove_(info *reg, struct fila *fila) {
    if (!fila || fila->tamanho == 0) return 0;
 
    *reg = fila->heap[0];
    fila->tamanho--;
 
    if (fila->tamanho == 0) return 1;
 
    fila->heap[0] = fila->heap[fila->tamanho];
 
    int pos = 0;
    while (1) {
        int esq   = 2 * pos + 1;
        int dir   = 2 * pos + 2;
        int maior = pos;
 
        if (esq < fila->tamanho && fila->compara(&fila->heap[esq], &fila->heap[maior]))
            maior = esq;
        if (dir < fila->tamanho && fila->compara(&fila->heap[dir], &fila->heap[maior]))
            maior = dir;
 
        if (maior == pos) break;
 
        troca(&fila->heap[pos], &fila->heap[maior]);
        pos = maior;
    }
 
    return 1;
}


int buscaNaFrente(info *reg, struct fila *fila){
    if(!fila || fila->tamanho == 0) return 0;
    *reg = fila->heap[0];
    return 1;
}


int buscaNaCauda(info *reg, struct fila *fila){
    if(!fila || fila->tamanho == 0) return 0;

    *reg = fila->heap[fila->tamanho - 1];
    return 1;
}


int testaVazia(struct fila *fila){
    if(!fila || fila->tamanho == 0) return 1;
    return 0;
}


int tamanhoDaFila(struct fila *fila){
    if(!fila) return 0;
    return fila->tamanho;
}


int reinicia(struct fila *fila){
    if(!fila) return 0;
    fila->tamanho = 0;
    return 1;
}


struct fila * destroi(struct fila *fila){
    if(fila){
        free(fila->heap);
        free(fila);
    }
    
    return NULL;
}