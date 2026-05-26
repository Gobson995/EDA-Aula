#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct noLDE {
    Info dados;
    struct noLDE *prox;
    struct noLDE *ant;
} No;

typedef struct lde {
    No *inicio;
    No *fim;
    int quantidade;
} LDE;

LDE* cria() {
    LDE *l = (LDE *) malloc(sizeof(LDE));
    if (l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
        l->quantidade = 0;
    }

    return l;
}

int vazia(LDE *l) {
    return (l->quantidade == 0);
} 

int tamanho(LDE *l) {
    return l->quantidade;
}

int insereNaPosicao(LDE *l, Info valor, int pos) {
    if (pos < 1 || pos > l->quantidade + 1) return 0;

    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return 0;
    novo->dados = valor;

    if (vazia(l)) {
        novo->prox = NULL;
        novo->ant = NULL;
        l->inicio = l->fim = novo;
    }
    else if (pos == 1) {
        novo->prox = l->inicio;
        novo->ant = NULL;
        l->inicio->ant = novo;
        l->inicio = novo;
    }
    else if (pos == l->quantidade + 1) {
        novo->prox = NULL;
        novo->ant = l->fim;
        l->fim->prox = novo;
        l->fim = novo;
    }
    else {
        No *atual;
        
        if (pos <= l->quantidade / 2) {
            atual = l->inicio;
            for (int i = 1; i < pos; i++) atual = atual->prox;
        }
        else {
            atual = l->fim;
            for (int i = l->quantidade; i > pos; i--) atual = atual->ant;
        }

        novo->prox = atual;
        novo->ant = atual->ant;

        atual->ant->prox = novo;
        atual->ant = novo;
    }

    l->quantidade++;
    return 1;
}

int removeNaPosicao(LDE *l, int pos, Info *saida) {
    if (vazia(l) || pos < 1 || pos > l->quantidade) return 0;

    No *aux;

    if (l->quantidade == 1) {
        aux = l->inicio;
        l->inicio = l->fim = NULL;
    }
    else if (pos == 1) {
        aux = l->inicio;
        l->inicio = aux->prox;
        l->inicio->ant = NULL;
    }
    else if (pos == l->quantidade) {
        aux = l->fim;
        l->fim = aux->ant;
        l->fim->prox = NULL;
    }
    else {
        if (pos <= l->quantidade / 2) {
            aux = l->inicio;
            for (int i = 1; i < pos; i++) aux = aux->prox;
        } else {
            aux = l->fim;
            for (int i = l->quantidade; i > pos; i--) aux = aux->ant;
        }
        
        aux->prox->ant = aux->ant;
    }

    *saida = aux->dados;
    free(aux);
    l->quantidade--;
    return 1;
}

void reinicia (LDE *l) {
    Info lixo;
    while (!vazia(l)) removeNaPosicao(l, 1, &lixo);
}

void destroi(LDE *l) {
    if (l != NULL) {
        reinicia(l);
        free(l);
    }
}

int main() {
    printf("=== TESTE MESTRE: LDE (Busca Inteligente) ===\n\n");

    LDE *lista = cria();
    Info val;

    printf("1. Inserindo elementos:\n");
    val.dado = 10; insereNaPosicao(lista, val, 1); // [10]
    val.dado = 30; insereNaPosicao(lista, val, 2); // [10] -> [30]
    val.dado = 40; insereNaPosicao(lista, val, 3); // [10] -> [30] -> [40]
    
    // Inserindo no meio (Posicao 2)
    val.dado = 20; insereNaPosicao(lista, val, 2); 
    printf("Lista esperada: [10] -> [20] -> [30] -> [40]\n\n");

    printf("--- Varrendo do INICIO para o FIM (Via 'prox') ---\n");
    No *atual = lista->inicio;
    while(atual != NULL) {
        printf("[%d] -> ", atual->dados.dado);
        atual = atual->prox;
    }
    printf("NULL\n\n");

    printf("--- Varrendo do FIM para o INICIO (Via 'ant') ---\n");
    atual = lista->fim;
    while(atual != NULL) {
        printf("[%d] -> ", atual->dados.dado);
        atual = atual->ant;
    }
    printf("NULL\n\n");

    printf("2. Removendo a posicao 3 (Devera ser o 30):\n");
    Info removido;
    removeNaPosicao(lista, 3, &removido);
    printf("Removido: %d\n\n", removido.dado);

    printf("Lista Final do Início para o Fim:\n");
    atual = lista->inicio;
    while(atual != NULL) {
        printf("[%d] -> ", atual->dados.dado);
        atual = atual->prox;
    }
    printf("NULL\n");

    destroi(lista);
    return 0;
}