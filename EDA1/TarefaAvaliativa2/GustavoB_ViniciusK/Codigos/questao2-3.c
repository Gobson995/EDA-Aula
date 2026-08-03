#include "arq.h"
#include <time.h>

#define MAX_DADOS 10000

int porMatricula(info *a, info *b) {
    return a->matricula > b->matricula;
}

void embaralhaArray(info *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        info temp = array[i];
        array[i]  = array[j];
        array[j]  = temp;
    }
}

int main() {
    FILE *csv = fopen("../Dados/dataset_v1.csv", "r");
    if (!csv) {
        printf("Erro: nao foi possivel abrir o dataset_v1.csv\n");
        return 1;
    }

    info *dados = malloc(MAX_DADOS * sizeof(info));
    if (!dados) {
        fclose(csv);
        printf("Erro: sem memoria.\n");
        return 1;
    }

    char linha[256];
    fgets(linha, sizeof(linha), csv);

    int total = 0;
    while (total < MAX_DADOS && fgets(linha, sizeof(linha), csv)) {
        sscanf(linha, "%49[^,],%d,%d,%49[^\n]",
               dados[total].nome,
               &dados[total].matricula,
               &dados[total].ranking,
               dados[total].curso);
        total++;
    }
    fclose(csv);
    printf("Registros lidos: %d\n", total);

    srand(42);
    embaralhaArray(dados, total);

    int bases[] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000,
                   4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
    int numBases = sizeof(bases) / sizeof(bases[0]);

    FILE *saida = fopen("../Analise/resultados.csv", "w");
    if (!saida) {
        printf("Erro: nao foi possivel criar resultados.csv\n");
        free(dados);
        return 1;
    }
    fprintf(saida, "N,media_iters\n");

    for (int b = 0; b < numBases; b++) {
        int N = bases[b];

        struct fila *fila = cria(sizeof(info), porMatricula);
        if (!fila) {
            printf("Erro ao criar fila para N=%d\n", N);
            continue;
        }

        long long somaIters = 0;
        for (int i = 0; i < N; i++) {
            insere(&dados[i], fila);
            somaIters += fila->itersInseracao;
        }

        double media = (double)somaIters / N;
        fprintf(saida, "%d,%.6f\n", N, media);
        printf("A%-5d  media = %.6f\n", N, media);

        destroi(fila);
    }

    fclose(saida);
    free(dados);
    printf("\nPronto! Resultados salvos em resultados.csv\n");
    return 0;
}