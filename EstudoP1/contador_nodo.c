#include <stdio.h>
#include <stdlib.h>
#include "fazendo_PSE.c"

int contaNodo (Pilha *p) {
    if (p == NULL) return 0;

    int contador = 0;
    No *aux = p->topo;

    while (aux != NULL) {
        aux = aux->abaixo;
        contador++;
    }
    return contador;
}