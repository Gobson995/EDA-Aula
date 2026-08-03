#include "arq.h"

int porMatricula(info *a, info *b) {
    return a->matricula > b->matricula;
}


void exibeMenu() {
    printf("\n--- Teste Heap Priority Queue ---\n");
    printf("1. Inserir elemento\n");
    printf("2. Remover elemento (Maior prioridade)\n");
    printf("3. Buscar na frente (Raiz)\n");
    printf("4. Buscar na cauda (Ultimo do array)\n");
    printf("5. Tamanho da fila\n");
    printf("6. Reiniciar (Limpar)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    struct fila *fila = cria(sizeof(info), porMatricula);
    int opcao = -1;
    info temp;

    while(opcao != 0){
        exibeMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome: ");
                scanf(" %49[^\n]", temp.nome);
                printf("Matricula: ");
                scanf("%d", &temp.matricula);
                printf("Ranking: ");
                scanf("%d", &temp.ranking);
                printf("Curso: ");
                scanf(" %49[^\n]", temp.curso);
 
                if (insere(&temp, fila)) {
                    printf("Inserido! Iteracoes no heapify-up: %d\n", fila->itersInseracao);
                } else {
                    printf("Erro ao inserir.\n");
                }
                break;
 
            case 2:
                if (remove_(&temp, fila)) {
                    printf("Removido! Matricula: %d | Nome: %s\n", temp.matricula, temp.nome);
                } else {
                    printf("Fila vazia.\n");
                }
                break;
 
            case 3:
                if (buscaNaFrente(&temp, fila)) {
                    printf("Frente -> Matricula: %d | Nome: %s\n", temp.matricula, temp.nome);
                } else {
                    printf("Fila vazia.\n");
                }
                break;
 
            case 4:
                if (buscaNaCauda(&temp, fila)) {
                    printf("Cauda -> Matricula: %d | Nome: %s\n", temp.matricula, temp.nome);
                } else {
                    printf("Fila vazia.\n");
                }
                break;
 
            case 5:
                printf("Tamanho atual: %d\n", tamanhoDaFila(fila));
                break;
 
            case 6:
                reinicia(fila);
                printf("Fila reiniciada.\n");
                break;
 
            case 0:
                printf("Encerrando...\n");
                break;
 
            default:
                printf("Opcao invalida.\n");
        }
    }
    destroi(fila);
    return 0;
}