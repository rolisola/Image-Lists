#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img.h"
#include "string.h"
#include "lista_dinamica.h"

int main() {
    // Exemplo de uso das funções
    imglist* my_list = create_list("barbara.pgm");

    insert_element(my_list, "exemplo.pgm");
    insert_element(my_list, "baboon.pgm");

    print_list(my_list);

    save_list_file(my_list, "lista.bin");

    // Liberar a memória alocada pela lista
    free_list(my_list);

    // Carregar a lista de um arquivo binário
    imglist* loaded_list = load_list("lista.bin");

    // Imprimir a lista carregada
    print_list(loaded_list);

    // Liberar a memória alocada pela lista carregada
    free_list(loaded_list);

    return 0;
}
