#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dado;
    struct nodo *abaixo;
} No;

typedef struct pilha {
    No *topo;
} Pilha;


Pilha* cria() {
    Pilha *p = (Pilha *) malloc (sizeof(Pilha));

    if (p != NULL) {
        p->topo = NULL;
    }
    return p;
}

int vazia(Pilha *p) {
    return (p->topo == NULL);
}

void empilha (Pilha *p, int valor) {
    No *novo = (No *) malloc (sizeof(No));

    if (novo == NULL) return;

    novo->dado = valor;
    novo->abaixo = p->topo;
    p->topo = novo;
}

int desempilha(Pilha *p) {
    if (vazia(p)) return -1;

    int valor = p->topo->dado;

    No *aux = p->topo;
    p->topo = aux->abaixo;
    free(aux);

    return valor;
}

int busca(Pilha *p) {
    if (vazia(p)) return -1;

    int valor_topo = p->topo->dado;

    return valor_topo;
}

void reinicia(Pilha *p) {
    while (p->topo != NULL) {
        desempilha(p);
    }
}

void destroi (Pilha *p) {
    reinicia(p);
    free(p);
}

void inverte(Pilha *p) {
    if (p == NULL || p->topo == NULL) return;

    No *atual = p->topo;
    No *anterior = NULL;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->abaixo;
        atual->abaixo = anterior;

        anterior = atual;
        atual = proximo;
    }

    p->topo = anterior;

}

int main () {
    Pilha *minhaPilha = cria();

    empilha(minhaPilha, 10); 
    empilha(minhaPilha, 20);
    empilha(minhaPilha, 30);

    inverte(minhaPilha);

    int valor1 = desempilha(minhaPilha);
    int valor2 = desempilha(minhaPilha);
    int valor3 = desempilha(minhaPilha);

    printf("A pilha estava %d [topo], %d e %d ", valor1, valor2, valor3);    
    
    return 0;
}
