#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct noFDE {
    Info dados;
    struct noFDE *defronte;
    struct noFDE *atras;
} No;

typedef struct fde {
    No *frente;
    No *cauda;
    int quantidade;
} FDE;

FDE* cria() {
    FDE *f = (FDE *) malloc(sizeof(FDE));

    if (f != NULL ){
        f->frente = NULL;
        f->cauda = NULL;
        f->quantidade = 0;
    }

    return f;
}

int vazia(FDE *f) {
    return (f->frente == NULL);
}

int insere (FDE *f, Info valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return 0;

    novo->dados = valor;
    novo->atras = NULL;
    novo->defronte = f->cauda;

    if (vazia(f)) f->frente = novo;
    else f->cauda->atras = novo;

    f->cauda = novo;
    f->quantidade++;

    return 1;
}

int inserePrioridade (FDE *f, Info valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return 0;

    novo->dados = valor;
    novo->defronte = NULL;
    novo->atras = NULL;

    if (vazia(f)) { /// fila vazia, tanto faz
        f->frente = novo;
        f->cauda = novo;
        f->quantidade++;

        return 1;
    }

    if (valor.dado > f->frente->dados.dado) { // fura a fila e vai para frente
        novo->atras = f->frente;
        f->frente->defronte = novo;
        f->frente = novo;
        f->quantidade++;
        
        return 1;
    }

    if (valor.dado <= f->cauda->dados.dado) { // vai para o final da fila
        novo->defronte = f->cauda;
        f->cauda->atras = novo;
        f->cauda = novo;
        f->quantidade++;

        return 1;
    }

    // no meio da fila

    No *atual = f->frente->atras;

    while (atual != NULL) {
        if (valor.dado > atual->dados.dado) {
            novo->defronte = atual->defronte;
            novo->atras = atual;

            atual->defronte->atras = novo;
            atual->defronte = novo;

            f->quantidade++;

            return 1;
        }
        atual = atual->atras;
    }

    return 1;
}

int remove_ (FDE *f, Info *saida) {
    if (vazia(f)) return 0;

    No *aux = f->frente;
    *saida = aux->dados;

    f->frente = aux->atras;

    if (f->frente == NULL) f->cauda = NULL;
    else f->frente->defronte = NULL;

    free(aux);
    f->quantidade--;

    return 1;
}

int tamanho(FDE *f) {
    return f->quantidade;
}

void reinicia(FDE *f) {
    Info lixo;
    while (!vazia(f)){
        remove_(f, &lixo);
    }
}

void destroi (FDE *f) {
    if (f != NULL) {
        reinicia(f);
        free(f);
    }
}


// testando com o main

int main() {
    printf("=== TESTE: FILA DE PRIORIDADE ===\n\n");

    FDE *clinica = cria();

    Info p1 = {30}; // Chega paciente de 30 anos
    Info p2 = {50}; // Chega paciente de 50 anos (Deve passar o de 30)
    Info p3 = {25}; // Chega paciente de 25 anos (Vai para o fim)
    Info p4 = {40}; // Chega paciente de 40 anos (Deve ficar entre o 50 e o 30)

    printf("1. Chegou paciente de %d anos.\n", p1.dado);
    inserePrioridade(clinica, p1);
    
    printf("2. Chegou paciente de %d anos.\n", p2.dado);
    inserePrioridade(clinica, p2);
    
    printf("3. Chegou paciente de %d anos.\n", p3.dado);
    inserePrioridade(clinica, p3);
    
    printf("4. Chegou paciente de %d anos.\n", p4.dado);
    inserePrioridade(clinica, p4);

    printf("\n--- ORDEM FINAL DA FILA ---\n");
    printf("A ler (da Frente para a Cauda): ");
    No *atual = clinica->frente;
    while(atual != NULL) {
        printf("[%d anos] -> ", atual->dados.dado);
        atual = atual->atras;
    }
    printf("NULL\n");

    destroi(clinica);
    return 0;
}

