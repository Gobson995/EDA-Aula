#include <stdio.h>
#include <stdlib.h>

    //  nó de cada caixinha da pilha
typedef struct nodo {
    int dado; // valor que a caixa armazena
    struct nodo *abaixo; // ponteiro para quem estiver embaixo dela
} No;

    // gerente da pila, fala onde a pilha começa (o topo)
typedef struct pilha {
    No *topo;
} Pilha;


int main () {
    Pilha *p = NULL; // um ponteiro para o gerente da pilha

    p = (Pilha *) malloc (sizeof(Pilha)); // aloca espaço para o gerente

    // ve se o malloc funcionou
    if (p != NULL) {
        p->topo = NULL;// diz que o topo da pilha esta vazia

        printf("Pilha criada com sucesso!\n");
        printf("Endereco do gerente p: %p\n", (void*)p);
        printf("Estado atual do topo: %p (NULL)\n", (void*)p->topo);
    }
    else {
        printf("Erro critico: Falha ao alocar memoria!\n");
        return 1; // Encerra o programa com erro 
    }

    return 0;
}