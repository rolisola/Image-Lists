#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img.h"
#include "string_handling.h"
#include "lista_dinamica.h"

void ajuda() {
    printf("\nUse como argumentos: lista.bin 'função desejada' 'nome do arquivo' 'valor da limiarização apenas para a função limiar'\n");
    printf("Possiveis funções:\n  criar: cria lista com o arquivo fornecido\n  imprimir: imprime a lista\n  inserir: insere arquivo na lista\n  remover: remove arquivo da lista\n  limiar: realiza a limiarização do arquivo com o valor fornecido no final\n  inversa: cria imagem inversa da fornecida\n  espVert: cria imagem espelhada verticalmente da fornecida\n  espHor: cria imagem espelhada horizontalmente da fornecida\n\n  para realizar as funções de manipulação de imagem em todos os arquivos da lista, não especifique algum arguivo\n");
}

int main(int argc, char *argv[]) {
    switch (argc) {
    case 3:
        if (compare_text(argv[1], "lista.bin") == 0 && compare_text(argv[2], "imprimir") == 0) {
            imglist *my_list = load_list(argv[1]);
            print_list(my_list);
        }
        break;

    case 4:
        if (compare_text(argv[2], "criar") == 0) {
            imglist *my_list = create_list(argv[3]);
            save_list_file(my_list, argv[1]);
            free_list(my_list);
        } else if (compare_text(argv[2], "inserir") == 0) {
            imglist *my_list = load_list(argv[1]);
            insert_element(my_list, argv[3]);
            save_list_file(my_list, argv[1]);
            free_list(my_list);
        } else if (compare_text(argv[2], "remover") == 0) {
            imglist *my_list = load_list(argv[1]);
            remove_element(my_list, argv[3]);
            save_list_file(my_list, argv[1]);
            free_list(my_list);
        } else if (compare_text(argv[2], "inversa") == 0) {
            FILE *my_file = fopen(argv[3], "rb");
            imgb *my_img = read_img(my_file);
            inversa(my_img);
            write_imgb(concat_string(argv[3], argv[2], ".pgm"), my_img);
            free(my_img);
            fclose(my_file);
        } else if (compare_text(argv[2], "espVert") == 0) {

        } else if (compare_text(argv[2], "espHor") == 0) {

        } else {
            ajuda();
        }
        break;
    case 5:
        if (compare_text(argv[2], "limiar") == 0) {
            FILE *my_file = fopen(argv[3], "rb");
            imgb *my_img = read_img(my_file);
            int limiar_value = atoi(argv[4]);
            if (limiar_value < 0 || limiar_value > my_img->cinza) {
                printf("Valor limiar invalido");
            } else {
                limiar(my_img, limiar_value);
                write_imgb(concat_string(argv[3], "limiar", ".pgm"), my_img);
                free_imgb(my_img);
                fclose(my_file);
            }
        } else {
            ajuda();
        }
        break;
    default:
        printf("Erro: entrada de argumentos invalida!\n");
        ajuda();
        exit(EXIT_FAILURE);
        break;
    }

    return 0;
}
