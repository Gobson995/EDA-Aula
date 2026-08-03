#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    char dado;
    struct nodo *abaixo;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

Pilha* cria () {
    Pilha *p = (Pilha *) malloc (sizeof(Pilha));

    if (p != NULL) {
        p->topo = NULL;
    }

    return p;
}

void empilha (Pilha *p, char valor) {
    No *novo = (No *) malloc (sizeof(No));

    if (novo == NULL) return;

    novo->dado = valor;
    novo->abaixo = p->topo;
    p->topo = novo;
}

void desempilha (Pilha *p) {
    if (p->topo == NULL) return;

    No *aux = p->topo;
    p->topo = aux->abaixo;
    free(aux);
}

int main () {
    Pilha *p = cria();

    int t = 13;

    while (t--) {
        char c;
        
        scanf(" %c", &c);

        if (c == '[' || c == '{' || c == '(') {
            empilha(p, c);
        }

        if (c == '}' || c == ']' || c == ')') {
            if (p->topo == NULL) {
                printf("Ta vazia, não bateu");
                break;
            }

            if (c == ']' && p->topo->dado == '[') desempilha(p);
            else if (c == '}' && p->topo->dado == '{') desempilha(p);
            else if (c == ')' && p->topo->dado == '(') desempilha(p);
            else {
                printf("Deu erro, não bateu");
                break;
            }
        }
    }

}
