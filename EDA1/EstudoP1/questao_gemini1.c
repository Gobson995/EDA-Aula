/*

int validaExpressao (char *expressao) {
    Pilha *p = cria();

    for (int i = 0; expressao[i] != '\0'; i++) {
        char letra = expressao[i];
        if (letra == '(' || letra == '{' || letra == '[') {
            empilha(p, letra);
        }

        if (letra == ')' || letra == '}' || letra == ']') {
            char *saida;
            if (vazia(p)) return 0;
            desempilha(p, *saida);

            if (saida == '(') {
                if (letra == '}' || letra == ']') return 0; 
            }
            else if (saida == '{') {
                if (letra == ')' || letra == ']') return 0; 
            }
            else {
                if (letra == '}' || letra == ')') return 0; 
            }
        }
    }
    if (vazia(p)) return 1;
    return 0;
}

*/