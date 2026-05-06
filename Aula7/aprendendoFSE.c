#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    int dado;
} Info;

typedef struct noFSE {
    Info dados;
    struct noFSE *atras;
} No;

typedef struct fse {
    No *frente;
    No *cauda;
    int quantidade;
} FSE;

FSE* cria() {
    FSE *f = (FSE *) malloc(sizeof(FSE));
    if (f != NULL) {
        f->frente = NULL;
        f->cauda = NULL;
        f->quantidade = 0; 
    }

    return f;
}

int vazia(FSE *f) {
    return (f->frente == NULL);
}

int insere (FSE *f, Info valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) return 0;

    novo->dados = valor;
    novo->atras = NULL;

    if (vazia(f)) {
        f->frente = novo;
    }
    else {
        f->cauda->atras = novo;
    }

    f->cauda = novo;
    f->quantidade++;

    return 1;
}

int remove_ (FSE *f, Info *saida) {
    if (vazia(f)) return 0;

    No *aux = f->frente; // segura o nó da frente

    *saida = aux->dados;

    f->frente = aux->atras; // a frente vai ser o cara que ta atras do primeiro

    // se a fila ficou vazia, a cauda também deve ser limpa
    if (f->frente == NULL) f->cauda = NULL;

    free(aux);
    f->quantidade--;

    return 1;
}

int buscaNaFrente (FSE *f, Info *saida) {
    if (vazia(f)) return 0;

    *saida = f->frente->dados;

    return 1;
}

int tamanho (FSE *f) {
    return f->quantidade;
}

void reinicia (FSE *f) {
    Info lixo;

    while (!vazia(f)) {
        remove_(f, &lixo);
    }
}

void destroi (FSE *f) {
    if (f != NULL) {
        reinicia(f);
        free(f);
    }
}

int main() {
    FSE *minhaFila = cria();

    if (minhaFila == NULL) {
        printf("Erro ao criar a fila\n");
        return 1;
    }

    printf("[+] Fila criada com sucesso. Vazia? %s\n", vazia(minhaFila) ? "SIM" : "NAO");

    // 2. Simulando a chegada de pacientes (Inserção na Cauda)
    Info p1 = {10}; // Senha 10
    Info p2 = {20}; // Senha 20
    Info p3 = {30}; // Senha 30

    printf("\n--- Chegada de Pacientes ---\n");
    insere(minhaFila, p1);
    printf("Paciente com senha %d entrou na fila.\n", p1.dado);
    
    insere(minhaFila, p2);
    printf("Paciente com senha %d entrou na fila.\n", p2.dado);
    
    insere(minhaFila, p3);
    printf("Paciente com senha %d entrou na fila.\n", p3.dado);

    // 3. Verificando o status atual
    printf("\n--- Status da Fila ---\n");
    printf("Tamanho atual: %d pacientes aguardando.\n", tamanho(minhaFila));

    Info proximo;
    if (buscaNaFrente(minhaFila, &proximo)) {
        printf("O proximo a ser atendido e a senha: %d\n", proximo.dado);
    }

    // 4. Simulando o atendimento (Remoção da Frente)
    printf("\n--- Iniciando Atendimentos ---\n");
    Info atendido;
    
    // Removendo o primeiro
    if (remove_(minhaFila, &atendido)) {
        printf("Atendendo paciente senha: %d (Correto? SIM, foi o 1o a chegar!)\n", atendido.dado);
    }

    // Verificando quem ficou na frente agora
    if (buscaNaFrente(minhaFila, &proximo)) {
        printf("Nova frente da fila: senha %d\n", proximo.dado);
    }

    // Removendo o segundo
    if (remove_(minhaFila, &atendido)) {
        printf("Atendendo paciente senha: %d\n", atendido.dado);
    }

    printf("Tamanho atual: %d pacientes aguardando.\n", tamanho(minhaFila));

    // 5. Testando a limpeza e destruição
    printf("\n--- Limpeza e Encerramento ---\n");
    printf("Esvaziando o resto da fila...\n");
    reinicia(minhaFila);
    printf("Fila Vazia? %s\n", vazia(minhaFila) ? "SIM" : "NAO");

    destroi(minhaFila);
    printf("[+] Fila destruida e memoria liberada com sucesso!\n");

    return 0;
} 