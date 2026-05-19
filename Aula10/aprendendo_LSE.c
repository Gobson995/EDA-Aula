#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct noLSE {
    Info dados;
    struct noLSE *prox;
} No;

typedef struct descLSE {
    No *inicio;
    int quantidade;
} LSE;

LSE* cria() {
    LSE *l = (LSE *) malloc(sizeof(LSE));
    if (l != NULL) {
        l->inicio = NULL;
        l->quantidade = 0;
    }

    return l;
}

int vazia(LSE *l) {
    return (l->quantidade == 0);
}

int tamanho(LSE *l) {
    return l->quantidade;
}

int insereNaPosicao(LSE *l, Info valor, int pos) {
    if (pos < 1 || pos > l->quantidade + 1) {
        printf("Erro: Posicao %d invalida na insercao!\n", pos);
        return 0;
    }

    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return 0;

    novo->dados = valor;

    if (pos == 1) {
        novo->prox = l->inicio;
        l->inicio = novo;
    }
    else {
        No *atual = l->inicio;

        for (int i = 1; i < pos -1; i++) {
            atual = atual->prox;
        }

        novo->prox = atual->prox;
        atual->prox = novo;
    }

    l->quantidade++;
    return 1;
}

int removeNaPosicao(LSE *l, int pos, Info *saida) {
    if (vazia(l) || pos < 1 || pos > l->quantidade) {
        printf("ERRO: Posicao %d invalida para remocao!\n", pos);
        return 0;
    }

    No *aux;

    if (pos == 1) {
        aux = l->inicio;
        *saida = aux->dados;
        l->inicio = aux->prox;
    }
    else {
        No *anterior = l->inicio;

        for (int i = 1; i < pos - 1; i++) {
            anterior = anterior->prox;
        }

        aux = anterior->prox;
        *saida = aux->dados;

        anterior->prox = aux->prox;
    }

    free(aux);
    l->quantidade--;
    return 1;
}

void reinicia(LSE *l) {
    Info lixo;

    while (!vazia(l)) {
        removeNaPosicao(l, 1, &lixo);
    }
}

void destroi(LSE *l) {
    if (l != NULL) {
        reinicia(l);
        free(l);
    }
}



int main() {
    printf("=== TESTE MESTRE: LSE (Posicoes Logicas) ===\n\n");

    LSE *minhaLista = cria();
    Info val;

    printf("1. Testando as restricoes de seguranca:\n");
    val.dado = 99;
    insereNaPosicao(minhaLista, val, 30); // Vai dar erro!

    printf("\n2. Inserindo elementos:\n");
    val.dado = 10;
    insereNaPosicao(minhaLista, val, 1); // Lista: [10]
    printf("Inseriu 10 na pos 1.\n");

    val.dado = 30;
    insereNaPosicao(minhaLista, val, 2); // Lista: [10] -> [30]
    printf("Inseriu 30 na pos 2.\n");

    val.dado = 20;
    insereNaPosicao(minhaLista, val, 2); // Lista: [10] -> [20] -> [30] (O 30 foi empurrado!)
    printf("Inseriu 20 na pos 2. O 30 deve ter ido para a pos 3.\n");

    printf("\n--- Lendo a Lista ---\n");
    No *atual = minhaLista->inicio;
    int pos = 1;
    while(atual != NULL) {
        printf("Posicao %d: [%d]\n", pos, atual->dados.dado);
        atual = atual->prox;
        pos++;
    }

    printf("\n3. Removendo do meio (Posicao 2):\n");
    Info removido;
    if (removeNaPosicao(minhaLista, 2, &removido)) {
        printf("Elemento removido: %d\n", removido.dado);
    }

    printf("\n--- Lendo a Lista Apos Remocao ---\n");
    atual = minhaLista->inicio;
    pos = 1;
    while(atual != NULL) {
        printf("Posicao %d: [%d]\n", pos, atual->dados.dado);
        atual = atual->prox;
        pos++;
    }

    destroi(minhaLista);
    printf("\n[+] Lista destruida. Teste concluido.\n");

    return 0;
}