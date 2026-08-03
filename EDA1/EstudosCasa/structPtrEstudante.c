#include <stdio.h>

int main () {
    // criação da variavel de estudante

    struct estudante { // tipo de dado definido pelo usuario
        int nMatricula;
        char nome[30];
        float vMensalidade;
        char dataBacharelado[30];
    };

    struct estudante stud1, *ptr_stud1; // declara variavel do tipo struct estudante e do tipo ponteiro de struct estudante

    // leitura de dados usuario
    ptr_stud1 = &stud1;

    printf("\n Digite sua matricula: ");
    scanf("%d", &ptr_stud1->nMatricula); // operador de acesso
                // mesmo assim precisa passar o endereço que ela ta, para armazenar

    // exibir coleta de dados                
    printf("\n Voce esta matriculado. Confira sua matricula de novo: %d\n", ptr_stud1->nMatricula);
                                                                            // sem o & pois quer o valor
    
    return 0;
}