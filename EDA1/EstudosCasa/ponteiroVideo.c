#include <stdio.h>
#include <stdlib.h>

int main () {
    int var = 15;
    int *ptr;

    ptr = &var;

    printf("Conteudo de var           = %d\n", var);
    printf("Endereco de var           = %p\n", &var);
    printf("Conteudo apontado por ptr = %d\n", *ptr);
    printf("Endereco apontado por ptr = %p\n", ptr);
    printf("Endereco de ptr           = %p\n", &ptr);


    return 0;
}

// Ponteiros:

// *ptr : o apontado por, conteudo do endereço da variavel que ptr aponta
//  ptr : o endereço da variavel
// &ptr : o endereço do ponteiro

