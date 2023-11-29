#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_text(char *text_1, char *text_2) {
    // Usando a função strcmp para comparar os textos
    int result = strcmp(text_1, text_2);

    // Verificando o resultado da comparação
    if (result == 0) {
        return 0; // Textos são iguais
    } else {
        printf("ERRO: Nome do arquivo não encontrado\n");
        exit(EXIT_FAILURE);
    }
}

void compare_extension(char *text_1, char *text_2) {
    if (strstr(text_1, text_2) == NULL) {
        printf("Erro: O arquivo deve ter extensao %s\n", text_2);
        exit(EXIT_FAILURE);
    }
}

int file_exist(char *nomeArquivo, char *mode) {
    FILE *file = fopen(nomeArquivo, mode);

    if (file) {
        fclose(file); // Arquivo existe
        return 1;
    } else {
        return 0; // Arquivo não existe
    }
}