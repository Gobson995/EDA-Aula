#include <stdio.h>
#include <stdlib.h>
#include "arqPSE.h"

int main(){
    int n, m;

    // 1. LEITURA E PREPARAÇÃO
    printf("Digite o tamanho da matriz (linhas N e colunas M):\n");
    scanf("%d %d", &n, &m);

    struct stack *stk = cria();
    
    int mat[n][m];
    printf("A seguir digite a matriz de %dx%d (apenas 0 e 1):\n", n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &mat[i][j]);
        }
    }
    
    // Matriz de Rótulos inicializada com 0
    int vis[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            vis[i][j] = 0;
        }
    }

    // Deslocamentos para a Vizinhança-4 (Sul, Leste, Oeste, Norte)
    int dx[4] = {1, 0, 0, -1};
    int dy[4] = {0, 1, -1, 0};

    // 2. A BUSCA EM PROFUNDIDADE (ROTULAÇÃO)
    int multiplicador = 2; // Rótulos começam no 2 para não confundir com o '1' da matriz
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            
            // Se achou um pedaço de objeto ainda não visitado
            if(mat[i][j] == 1 && vis[i][j] == 0){
                vis[i][j] = multiplicador; 
                
                info reg = {i, j};
                insert(&reg, stk); // Empilha o pixel semente

                // Começa a explorar esse objeto
                while(!vazia(stk)){
                    info atual = first(stk); // "Olha" onde estamos
                    int achou = 0;
                    
                    // Testa os 4 lados do pixel atual
                    for(int k = 0; k < 4; k++){
                        int ni = atual.x + dx[k];
                        int nj = atual.y + dy[k];

                        // Se o vizinho está dentro da matriz, é parte do objeto ('1') e não foi visitado:
                        if(ni >= 0 && ni < n && nj >= 0 && nj < m && mat[ni][nj] == 1 && vis[ni][nj] == 0){
                            vis[ni][nj] = multiplicador; // Rotula
                            info aux = {ni, nj};
                            insert(&aux, stk);           // Empilha para visitar
                            achou = 1;
                            break; // Para o For! Entramos no novo vizinho.
                        }
                    }
                    
                    // Se olhou os 4 lados e não tem vizinhos válidos (Beco sem saída)
                    if(!achou){
                        pop(stk); // Tira da pilha (Backtracking para voltar um passo)
                    }
                }
                
                // Finalizou 100% de um objeto. Prepara para o próximo!
                multiplicador++;
            }
        }
    }

    // 3. ANÁLISE DE TAMANHO
    // Usa calloc para criar um vetor de contagem dinâmico e seguro, já inicializado em 0
    int *vector = calloc(multiplicador, sizeof(int));
    
    // Passa na matriz contando os pixels de cada rótulo
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(vis[i][j] >= 2){ // Só conta o que é objeto
                vector[vis[i][j]]++;
            }
        }
    }

    // Imprime o resultado final
    printf("\nMatriz Rotulada:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", vis[i][j]);
        }
        printf("\n");
    }

    // Descobre qual rótulo teve a maior contagem
    int indiceMaior = 0;
    int maiorTamanho = 0;
    
    for(int i = 2; i < multiplicador; i++){
        if(vector[i] > maiorTamanho){
            indiceMaior = i;
            maiorTamanho = vector[i];
        }
    }

    // 4. LIMPEZA E FINALIZAÇÃO
    if(indiceMaior >= 2){
        printf("\nA maior caixa eh a caixa com o rotulo %d (Tamanho: %d pixels)\n", indiceMaior, maiorTamanho);
    } else {
        printf("\nNenhuma caixa foi encontrada na matriz.\n");
    }

    free(vector);
    destroy(stk); // Libera a pilha

    return 0;
}