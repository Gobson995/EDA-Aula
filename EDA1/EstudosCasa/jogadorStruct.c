#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nick[15];
    int nivel;
} Jogador;

void uparNivel(Jogador *j) {
    j->nivel++;
}

int main () {

    // criando um ponteiro
    Jogador *p1 = NULL;

    // alocando a memória dinamicamente (construindo a casa)
    p1 = (Jogador *) malloc(sizeof(Jogador));

    // acessando o nick e o nivel da "planta"/struct via ponteiro
    strcpy(p1->nick, "Gobson");
    p1->nivel = 30;

    printf("O jogador %s esta no nivel %d\n", p1->nick, p1->nivel);

    printf("Parabens voce upou de nivel!!\n");

    uparNivel(p1);

    printf("Seu nivel agora eh: %d\n", p1->nivel);

    free(p1);

    return 0;
}