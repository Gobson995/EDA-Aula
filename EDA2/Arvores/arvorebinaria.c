#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    struct no* pai; 
    struct no* esquerda;
    struct no* direita; 
    float v;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

Arvore* cria() {
    Arvore *arvore;
    arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}

int vazia(Arvore* arvore) {
    return (arvore->raiz == NULL);
}

void adiciona(Arvore* arvore, float valor) {
    No *no = malloc(sizeof(No));

    if(vazia(arvore)){
        no->esquerda = NULL;
        no->direita = NULL;
        no->pai = no;
        arvore->raiz = no;
        no->v = valor;
        return;
    }
    
    No *antes = malloc(sizeof(No));
    No *atual = malloc(sizeof(No));
    atual = arvore->raiz;
    int id = 0;
    
    while(atual != NULL){
        if(atual->v > valor){
            antes = atual;
            atual = atual->esquerda;
            id = 0;
        }
        else{
            antes = atual;
            atual = atual->direita;
            id = 1;
        }
    }
    
    if(id == 0){
        antes->esquerda = no;
        no->pai = antes;
    }
    else{
        antes->direita = no;
        no->pai = antes;
    }

    no->v = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    return;
}

void remover(Arvore* arvore, No* no) {
    
    if(no->esquerda != NULL)
        remover(arvore, no->esquerda);
    if(no->direita != NULL)
        remover(arvore, no->direita);
    
    if(no->pai == NULL){
        arvore->raiz = NULL;
    }
    else{
        if(no->pai->esquerda == no)
            no->pai->esquerda = NULL;
        else
            no->pai->direita = NULL;
    }
    free(no);
}

void preOrdem(No* no){
    printf("%f ", no->v);
    if(no->esquerda != NULL) preOrdem(no->esquerda);
    if(no->direita != NULL) preOrdem(no->direita);
}

void inOrder(No* no){
    if(no->esquerda != NULL) inOrder(no->esquerda);
    printf("%f ", no->v);
    if(no->direita != NULL) inOrder(no->direita);
}

void posOrder(No* no){
    if(no->esquerda != NULL) posOrder(no->esquerda);
    if(no->direita != NULL) posOrder(no->direita);
    printf("%f ", no->v);
}

void largura(No* no) {
    
}

int main(){
    // Questao 4
    Arvore *a = cria();
    adiciona(a, 4);
    adiciona(a, 2);
    adiciona(a, 1);
    adiciona(a, 3);
    adiciona(a, 8);
    adiciona(a, 9);
    adiciona(a, 6);
    adiciona(a, 5);
    adiciona(a, 7);
    
    preOrdem(a->raiz);
    printf("\n");

    inOrder(a->raiz);
    printf("\n");

    posOrder(a->raiz);
    printf("\n");

    largura(a->raiz);
    printf("\n");
}