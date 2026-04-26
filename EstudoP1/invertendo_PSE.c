#include <stdio.h>
#include <stdlib.h>
#include "fazendo_PDE.c"

void inverte (Pilha *p) {
    if (vazia(p)) return;

    No *atual = p->topo;
    No *aux = NULL;

    while (atual != NULL) {
        aux = atual->abaixo; // guarda quem estava embaixo
        atual->abaixo = atual->acima; // o de baixo vira o de cima
        atual->acima = aux; // o de cima vira o de baixo

        if (atual->acima == NULL) {
            p->topo = atual;
        }

        atual = atual->acima;
    }
}