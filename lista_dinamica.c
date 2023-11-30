#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_dinamica.h"
#include "string_handling.h"

node* alloc_element(){
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    return new_node;
}

imglist* create_list(char* filename) {
    imglist* new_list = (imglist*)malloc(sizeof(imglist));
    if (new_list == NULL) {
        printf("Erro ao alocar memória para a lista");
        exit(EXIT_FAILURE);
    }

    node * new_node = alloc_element();

    compare_extension(filename, ".pgm");
    if (file_exist(filename, "rb") == 0){
        printf("!!!ERRO: Arquivo inexistente\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->filename, filename);
    new_node->next = NULL;

    new_list->head = new_node;

    return new_list;
}

void insert_element(imglist* list, char* filename) {
    compare_extension(filename, ".pgm");
    if (file_exist(filename, "rb") == 0){
        printf("ERRO: Arquivo inexistente\n");
        exit(EXIT_FAILURE);
    }

    node* new_node = alloc_element();

    strcpy(new_node->filename, filename);
    new_node->next = list->head;
    list->head = new_node;
}

void remove_element(imglist* list, char* filename) {
    compare_extension(filename, ".pgm");
    if (file_exist(filename, "rb") == 0){
        printf("ERRO: Arquivo inexistente\n");
        exit(EXIT_FAILURE);
    }
    node* current = list->head;
    node* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->filename, filename) == 0) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Erro: O arquivo %s nao foi encontrado na lista\n", filename);
}

void print_list(imglist* list) {
    int swapped;
    node* ptr_1;
    node* list_ptr = NULL;

    if (list->head == NULL) {
        printf("Lista vazia\n");
        return;
    }

    do {
        swapped = 0;
        ptr_1 = list->head;

        while (ptr_1->next != list_ptr) {
            if (strcmp(ptr_1->filename, ptr_1->next->filename) > 0) {
                char temp[50];
                strcpy(temp, ptr_1->filename);
                strcpy(ptr_1->filename, ptr_1->next->filename);
                strcpy(ptr_1->next->filename, temp);
                swapped = 1;
            }

            ptr_1 = ptr_1->next;
        }

        list_ptr = ptr_1;
    } while (swapped);

    printf("Lista de imagens em ordem alfabetica:\n");
    node* current = list->head;
    while (current != NULL) {
        printf("%s\n", current->filename);
        current = current->next;
    }
}

void save_list_file(imglist* list, char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita\n");
        exit(EXIT_FAILURE);
    }

    node* current = list->head;
    while (current != NULL) {
        fwrite(current, sizeof(node), 1, file);
        current = current->next;
    }

    fclose(file);
}

imglist* load_list(char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura\n");
        exit(EXIT_FAILURE);
    }

    imglist* new_list = (imglist*)malloc(sizeof(imglist));
    if (new_list == NULL) {
        printf("Erro ao alocar memória para a lista\n");
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;

    node read_node;
    size_t bytes_read;

    while ((bytes_read = fread(&read_node, sizeof(node), 1, file)) > 0) {
        node* new_node = alloc_element();

        strcpy(new_node->filename, read_node.filename);
        new_node->next = new_list->head;
        new_list->head = new_node;
    }

    fclose(file);

    return new_list;
}

void free_list(imglist* list) {
    node* current = list->head;
    node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}
