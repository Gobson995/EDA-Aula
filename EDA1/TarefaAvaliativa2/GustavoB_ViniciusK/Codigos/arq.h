#ifndef ARQ_H
#define ARQ_H
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define CAP_INICIAL 100
 
typedef struct {
    char nome[50];
    int matricula;
    int ranking;
    char curso[50];
} info;

typedef int (*Comparador)(info *a, info *b);
 
struct fila {
    info *heap;
    int capacidade;
    int tamanho;
    int tamInfo;
    int itersInseracao;
    Comparador compara;
};
 
struct fila * cria(int tamInfo, Comparador compara);
int insere(info *novo, struct fila *fila);
int remove_(info *reg, struct fila *fila);
int buscaNaFrente(info *reg, struct fila *fila);
int buscaNaCauda(info *reg, struct fila *fila);
int testaVazia(struct fila *fila);
int tamanhoDaFila(struct fila *fila);
int reinicia(struct fila *fila);
struct fila * destroi(struct fila *fila);
 
#endif