#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    No *refMovel;
    int quantidade;
} FDE;


FDE* cria() {
    FDE *f = (FDE *) malloc(sizeof(FDE));
    if (f != NULL) {
        f->frente = NULL;
        f->cauda = NULL;
        f->refMovel = NULL;
        f->quantidade = 0;
    }
    return f;
}

int vazia(FDE *f) {
    return (f->frente == NULL);
}

int inserePrioridade(FDE *f, Info valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return 0;
    
    novo->dados = valor;
    novo->defronte = NULL;
    novo->atras = NULL;

    // CASO 1: Fila Vazia
    if (vazia(f)) {
        f->frente = f->cauda = f->refMovel = novo;
        f->quantidade++;
        return 1;
    }

    // CASO 2: Nova Frente (Maior Prioridade - fura a fila toda)
    if (valor.dado > f->frente->dados.dado) {
        novo->atras = f->frente;
        f->frente->defronte = novo;
        f->frente = f->refMovel = novo;
        f->quantidade++;
        return 1;
    }

    // CASO 3: Nova Cauda (Menor Prioridade - vai para o fim)
    if (valor.dado <= f->cauda->dados.dado) {
        novo->defronte = f->cauda;
        f->cauda->atras = novo;
        f->cauda = f->refMovel = novo;
        f->quantidade++;
        return 1;
    }

    // CASO 4: Insercao no Meio Otimizada com refMovel
    No *atual;
    int distFrente = abs(f->frente->dados.dado - valor.dado);
    int distCauda = abs(f->cauda->dados.dado - valor.dado);
    int distRef = abs(f->refMovel->dados.dado - valor.dado);

    // 1. Escolhe o ponto de partida mais proximo (Otimizacao)
    if (distRef <= distFrente && distRef <= distCauda) {
        atual = f->refMovel;
    } else if (distFrente <= distCauda) {
        atual = f->frente;
    } else {
        atual = f->cauda;
    }

    // 2. Navegacao Bidirecional Inteligente
    if (valor.dado > atual->dados.dado) {
        // O novo e MAIS VELHO que o atual. Andamos para a FRENTE.
        while (atual != NULL && valor.dado > atual->dados.dado) {
            atual = atual->defronte;
        }
    } else {
        // O novo e MAIS NOVO que o atual. Andamos para TRAS.
        while (atual != NULL && valor.dado <= atual->dados.dado) {
            atual = atual->atras;
        }
        // Ajuste: Queremos que 'atual' seja sempre o no que ficara na FRENTE do novo.
        atual = atual->defronte;
    }

    // 3. O Encaixe Perfeito
    // Neste momento, 'atual' e exatamente o elemento que ficara na FRENTE do 'novo'.
    novo->defronte = atual;
    novo->atras = atual->atras;
    
    atual->atras->defronte = novo;
    atual->atras = novo;
    
    f->refMovel = novo; // Atualiza o referencial para insercoes futuras
    f->quantidade++;
    
    return 1;
}

int remove_(FDE *f, Info *saida) {
    if (vazia(f)) return 0;

    No *aux = f->frente;
    *saida = aux->dados;

    f->frente = aux->atras;

    if (f->frente == NULL) {
        // A fila esvaziou totalmente
        f->cauda = f->refMovel = NULL; 
    } else {
        f->frente->defronte = NULL;
        // Se o refMovel apontava para quem saiu, protegemos o ponteiro
        if (f->refMovel == aux) f->refMovel = f->frente;
    }

    free(aux);
    f->quantidade--;
    return 1;
}


void reinicia(FDE *f) {
    Info lixo;
    while (!vazia(f)) remove_(f, &lixo);
}

void destroi(FDE *f) {
    if (f != NULL) {
        reinicia(f);
        free(f);
    }
}

int main() {
    printf("=== TESTE MESTRE: FDE COM REFMOVEL ===\n\n");

    FDE *clinica = cria();

    // Ordem de chegada que forca a busca a testar os 3 caminhos
    Info p[] = {{30}, {50}, {20}, {40}, {45}, {25}}; 
    
    for(int i = 0; i < 6; i++) {
        printf("Inserindo paciente de %d anos...\n", p[i].dado);
        inserePrioridade(clinica, p[i]);
    }

    printf("\n--- ORDEM FINAL DA FILA (Maior para Menor) ---\n");
    printf("A ler: ");
    No *atual = clinica->frente;
    while(atual != NULL) {
        printf("[%d anos] -> ", atual->dados.dado);
        atual = atual->atras;
    }
    printf("NULL\n");

    destroi(clinica);
    printf("\n[+] Teste concluido com sucesso e memoria libertada.\n");
    return 0;
}