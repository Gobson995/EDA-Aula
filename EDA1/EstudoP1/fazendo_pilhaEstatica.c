#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int itens[100]; // vetor
    int topo; // o que aponta para o elemento do topo
} Pilha;

// começa uma pilha nova, com o topo inicializado
Pilha* cria() {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));

    if (p != NULL) {
        p->topo = -1; // fala que a pilha esta vazia, pois o indice do topo é -1
    }
    return p;
}

// verifica se a pilha esta vazia
int vazia (Pilha *p) {
    return (p->topo == -1);
}

// verifica se a pilha esta cheia
int cheia(Pilha *p) {
    return (p->topo == 100 - 1); // fala se esta cheia quando o topo apontar para o ultimo lugar disponivel no vetor
}

// adiciona mais um elemento na pilha
void empilha (Pilha *p, int valor) {
    if (cheia(p)) {
        printf("A pilha ja esta cheia!");
        return;
    }

    p->topo++; // sobe o topo uma posição
    p->itens[p->topo] = valor; // coloca o valor na posição que o topo esta
}

// remove um valor e retorna o valor que foi retirado
int desempilha(Pilha *p) {
    if (vazia(p)) {
        printf("A pilha esta vazia");
        return -1;
    }

    int valor_removido = p->itens[p->topo]; // pega o topo
    p->topo--; // descresce o topo

    return valor_removido;
}

// busca um valor solicitado na pilha. de cima para baixo
int busca (Pilha *p, int valor_busca) {
    for (int i = p->topo; i >= 0; i--) {
        if (p->itens[i] == valor_busca) {
            return i; // retorna a posição que ele esta
        }
    }

    return -1; // se não achar, retorna -1
}

// esvazia a pilha para ser usada de novo
void reinicia (Pilha *p) {
    p->topo = -1; // simplesmente, coloca o topo como "nulo", não precisa apagar os numeros
}

// liralmente destroi tudo
void destroi (Pilha *p) {
    if (p != NULL) {
        free(p); // libera o espaço 
    }
}


int main () {
    Pilha *minhaPilha = cria();

    empilha(minhaPilha, 10); 
    empilha(minhaPilha, 20);
    empilha(minhaPilha, 30);

    printf("O valor 20 esta no indice: %d\n", busca(minhaPilha, 20));
    
    printf("Desempilhando: %d\n", desempilha(minhaPilha));
    
    reinicia(minhaPilha);
    
    if (vazia(minhaPilha)) {
        printf("A pilha foi reiniciada e agora esta vazia!\n");
    }
    
    destroi(minhaPilha);
    
    return 0;
}



