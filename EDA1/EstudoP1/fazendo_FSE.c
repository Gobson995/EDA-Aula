#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int valor;
} Info;

typedef struct nodo {
    Info dado;
    struct nodo *proximo;
} No;

typedef struct fila {
    No *inicio;
    No *fim;
} Fila;

Fila* cria() {
    Fila *f = (Fila *) malloc (sizeof(Fila));
    
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
    }

    return f;
}

int vazia (Fila *f) {
    return (f->inicio == NULL);
}

int enfileirar (Fila *f, Info valor) {
    No *novo = (No *) malloc (sizeof(No)); // cria um novo nodo
    
    if (novo == NULL) return 0;

    novo->dado = valor; // recebe o valor
    novo->proximo = NULL; // não tem ninguem atras dele

    if (vazia(f)) f->inicio = novo; // se tiver vazio, é o primeio e o ultimo ao mesmo tempo
    else f->fim->proximo = novo; // se não, o antigo ultimo recebe o novo atras dele

    f->fim = novo; // atualiza o ultimo da fila como o novo

    return 1;
}

int desenfileirar (Fila *f, Info *saida) {
    if (vazia(f)) return 0;

    No *aux = f->inicio;  // segura o cara da frente
    *saida = aux->dado; // copia o primeiro da fila para a saida

    f->inicio = aux->proximo; // o começo vira o que tava atras do primeiro

    if (f->inicio == NULL) f->fim = NULL; // se fila esvaziou, o proximo vai ser NULL também

    free(aux); // libera
    return 1;
}

int frente (Fila *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->inicio->dado;

    return 1;
}

void destroi (Fila *f) {
    Info lixo;

    while (!vazia(f)) {
        desenfileirar(f, &lixo);
    }

    free(f);
}
