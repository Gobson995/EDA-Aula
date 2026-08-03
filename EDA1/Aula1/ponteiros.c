#include <stdio.h>
#include <stdint.h>

#define TEST 1

int main () {
    int x = 29, y = -33;
    int *p = NULL;
    int **pp = NULL;

    printf("\n TESTE %i \n", TEST);

    pp = &p;

    printf("\n endereço de 'x': %p \n", (void*)&x);
    printf(" endereço de 'y': %p \n", (void*)&y);
    printf(" endereço de 'p': %p \n", (void*)&p);
    printf(" endereço de 'pp': %p \n", (void*)&pp);
    printf(" 'p' aponta para: %p \n", (void*)p);
    printf(" 'pp' aponta para: %p \n", (void*)pp);

    printf("\n TECLE ENTER \n");
    //getchar();

    p = &x;
    pp = &p;

    printf("\n------------ Após as atribuições ----------------\n");

    printf("\n endereço de 'x': %p \n", (void*)&x);
    printf(" endereço de 'y': %p \n", (void*)&y);
    printf(" endereço de 'p': %p \n", (void*)&p);
    printf(" endereço de '*pp': %p \n", (void*)(*pp));
    printf(" endereço de 'pp': %p \n", (void*)&pp);
    printf(" 'p' aponta para: %p \n", (void*)p);
    printf(" 'pp' aponta para: %p \n", (void*)pp);

    printf("\n TECLE ENTER \n");
    //getchar();

    printf("\n--------- Exemplo 1: Indireção ------------\n");
    printf(" Lendo 'p' por meio de '*pp' == %p \n", (void*)*pp);
    printf(" Lendo 'x' por meio de '*p' == %i \n", *p);
    printf(" Lendo 'x' por meio de '**pp' == %i \n", **pp);

    *p = 94;
    printf(" Alterando 'x' por meio de '*p' = %i \n", *p);

    printf("\n TECLE ENTER \n");
    //getchar();

    printf("\n--------- Exemplo 2: Indireção ------------\n");

    *pp = &y;
    printf(" Alterando o endereço apontado por 'p' por meio de '*pp' = &y == %p \n", (void*)&y);
    printf(" Lendo 'y' por meio de '*p' == %i \n", *p);
    printf(" Lendo 'y' por meio de '**pp' == %i \n", **pp);

    printf("\n TECLE ENTER \n");
    //getchar();

    printf("\n---------- Exemplo 3: Indireção -----------\n");

    **pp = 137;
    printf(" Alterando 'y' por meio de '**pp' = %i \n", y);

    printf("\n ================= FIM TESTE %i \n\n", TEST);

    return 0;
}