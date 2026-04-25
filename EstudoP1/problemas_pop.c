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


void push(Pilha *p, int valor) {
    No *novo = (No *) malloc(sizeof(No)); // um terreno para uma nova caixa

    if (novo != NULL) {
        novo->dado = valor; // coloca o valor dentro do nó (caixa)

        novo->abaixo = p->topo; // a caixa aponta para quem estava no topo

        p->topo = novo; // o gerente atualiza o ponteiro oficial para a caixa nova

        printf("Empilhado com sucesso: %d\n", valor);
    }
    else {
         
    }
}

int pop(Pilha *p) {
    if (p != NULL && p->topo != NULL) {
        No *aux = p->topo; // auxiliar segura a caixa do topo
        p->topo = aux->abaixo; // o gerente olha para a caixa de baixo

        int conta = aux->dado;

        free(aux); // destroi o aux que criou

        printf("Item removido com sucesso\n");

        return conta;
    }
    else {
        printf("Nao tem nada, ou seja, nao tem como remover");
        return -1;
    } 
}


int main () {
    Pilha *p = NULL; // um ponteiro para so gerente da pilha

    p = (Pilha *) malloc (sizeof(Pilha)); // aloca espaço para o gerente

    // ve se o malloc funcionou
    if (p != NULL) {
        p->topo = NULL;// diz que o topo da pilha esta vazia

        push(p, 10);
        push(p, 20);
        push(p, 83);

        int conta = pop(p);

        printf("\nO valor que que foi retirado do topo da pilha eh: %d\n", conta);

        // Vamos provar que o topo mudou?
        printf("\nO valor que esta no TOPO agora e: %d\n", p->topo->dado);
        
        // Como o topo aponta para a caixa de baixo, podemos "espiar" a caixa 20:
        printf("Abaixo do topo esta o valor: %d\n", p->topo->abaixo->dado);
    }
    else {
        printf("Erro critico: Falha ao alocar memoria!\n");
        return 1; // Encerra o programa com erro 
    }

    return 0;
}