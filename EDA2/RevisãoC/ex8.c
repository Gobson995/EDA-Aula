#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodo {
    char dado;
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

void desempilha(Pilha *p) {
    if (vazia(p)) return;

    No *aux = p->topo;
    p->topo = aux->abaixo;
    free(aux);
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


int main () {
    char s[100];

    scanf(" %[^\n]", s);

    int tamanho = strlen(s);

    int resp = 0;

    Pilha *p = cria();

    for (int i = 0; i < tamanho; i++) {
        char c = s[i];

        if (c == ' ') continue;

        if (c == '(' || c == '[' || c == '{') {
            empilha(p, c);
        }
        
        if (c == '}' || c == ']' || c == ')') {
            if (p->topo == NULL) {
                resp++;
                break;
            }

            if (c == ']' && p->topo->dado == '[') desempilha(p);
            else if (c == '}' && p->topo->dado == '{') desempilha(p);
            else if (c == ')' && p->topo->dado == '(') desempilha(p);
            else {
                resp++;
                break;
            }
        }
    }

    if (resp == 0 && vazia(p)) printf("True\n");
    else printf("False\n");


    destroi(p);

    return 0;
}