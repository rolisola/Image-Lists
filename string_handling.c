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
        return 1;
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

// Função para remover a extensão de um texto
void remove_extension(char *texto) {
    char *ponto = strrchr(texto, '.'); // Encontra o último ponto na string
    if (ponto != NULL) {
        *ponto = '\0'; // Substitui o ponto por '\0' para remover a extensão
    }
}

// Função para concatenar dois textos, removendo a extensão do primeiro texto antes da concatenação
char *concat_string(char *str1, char *str2, char *extension) {
    // Copia o primeiro texto para evitar modificar o original
    char *texto1 = strdup(str1);

    // Remove a extensão do primeiro texto
    remove_extension(texto1);

    // Calcula o comprimento total necessário para as duas strings mais o caractere nulo
    size_t len1 = strlen(texto1);
    size_t len2 = strlen(str2);
    size_t len3 = strlen(extension);
    size_t lenTotal = len1 + len2 + len3 + 1;

    // Aloca memória para a nova string concatenada
    char *resultado = (char *)malloc(lenTotal);

    // Verifica se a alocação de memória foi bem-sucedida
    if (resultado == NULL) {
        fprintf(stderr, "Erro na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    // Copia o primeiro texto sem a extensão para o resultado
    strcpy(resultado, texto1);

    // Concatena a segunda string ao resultado
    strcat(resultado, str2);

    // Concatena a extensao ao resultado
    strcat(resultado, extension);

    // Libera a memória alocada para a cópia do primeiro texto
    free(texto1);

    // Retorna a string concatenada
    return resultado;
}
