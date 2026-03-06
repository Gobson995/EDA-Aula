#include <stdio.h>
#include <stdlib.h>

int main () {
    int *pontuacao = NULL; // declarando um ponteiro (sem valor, só o endereço)

    // não usa * pois quer guardar um endereço
    pontuacao = (int  *) malloc(sizeof(int)); // aloca o espaço exato de um inteiro
                                              // o sizeoff(int) calcula quantos bytes ocupa no sistema
                            
    // usa * pois quer guardar um valor
    *pontuacao = 100; // * => indireção simples (apontando), ir até o endereço e guardar o valor

    printf("Pontuação alocada: %d\n", *pontuacao);

    free(pontuacao); // libera espaço na memoria
    // destroi a casa e devolve o terreno

    return 0;
}