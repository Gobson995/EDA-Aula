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
    printf("=== INICIANDO TESTES DA FILA FDE (NIVEL 2) ===\n\n");

    // 1. Criando a Fila
    FDE *minhaFila = cria();
    if (minhaFila == NULL) {
        printf("Erro ao criar a fila!\n");
        return 1;
    }
    printf("[+] Fila FDE criada com sucesso. Vazia? %s\n", vazia(minhaFila) ? "SIM" : "NAO");

    // 2. Simulando a chegada de pacientes
    Info p1 = {100}; // Senha 100
    Info p2 = {200}; // Senha 200
    Info p3 = {300}; // Senha 300

    printf("\n--- Chegada de Pacientes ---\n");
    insere(minhaFila, p1);
    printf("Paciente %d entrou na fila.\n", p1.dado);
    
    insere(minhaFila, p2);
    printf("Paciente %d entrou na fila.\n", p2.dado);
    
    insere(minhaFila, p3);
    printf("Paciente %d entrou na fila.\n", p3.dado);

    printf("Tamanho atual: %d pacientes aguardando.\n", tamanho(minhaFila));

    // =================================================================
    // 🌟 A PROVA DOS NOVE: TESTANDO O DUPLO ENCADEAMENTO
    // =================================================================
    
    printf("\n--- Varrendo da FRENTE para a CAUDA (usando 'atras') ---\n");
    printf("A ler: ");
    No *atual = minhaFila->frente;
    while(atual != NULL) {
        printf("[%d] -> ", atual->dados.dado);
        atual = atual->atras; // Anda em direcao a cauda
    }
    printf("NULL\n");

    printf("\n--- Varrendo da CAUDA para a FRENTE (usando 'defronte') ---\n");
    printf("A ler: ");
    atual = minhaFila->cauda;
    while(atual != NULL) {
        printf("[%d] -> ", atual->dados.dado);
        atual = atual->defronte; // Anda em direcao a frente
    }
    printf("NULL\n");

    // =================================================================

    // 3. Simulando o atendimento (Remoção da Frente)
    printf("\n--- Iniciando Atendimentos ---\n");
    Info atendido;
    
    if (remove_(minhaFila, &atendido)) {
        printf("Atendendo paciente senha: %d (Correto? SIM, foi o 1o a chegar!)\n", atendido.dado);
    }
    
    if (remove_(minhaFila, &atendido)) {
        printf("Atendendo paciente senha: %d\n", atendido.dado);
    }

    printf("Tamanho atual: %d pacientes aguardando.\n", tamanho(minhaFila));

    // 4. Testando a limpeza e destruição
    printf("\n--- Limpeza e Encerramento ---\n");
    printf("Esvaziando o resto da fila...\n");
    destroi(minhaFila);
    printf("[+] Fila destruida e memoria liberada com sucesso!\n");

    return 0;
}