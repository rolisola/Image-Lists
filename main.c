#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char filename[50];
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} ImageList;

ImageList* createList(const char* filename) {
    ImageList* newList = (ImageList*)malloc(sizeof(ImageList));
    if (newList == NULL) {
        perror("Erro ao alocar memória para a lista");
        exit(EXIT_FAILURE);
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }

    if (strstr(filename, ".pgm") == NULL) {
        fprintf(stderr, "Erro: O arquivo deve ter extensao .pgm\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->filename, filename);
    newNode->next = NULL;

    newList->head = newNode;

    return newList;
}

void insertElement(ImageList* list, const char* filename) {
    if (strstr(filename, ".pgm") == NULL) {
        fprintf(stderr, "Erro: O arquivo deve ter extensao .pgm\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->filename, filename);
    newNode->next = list->head;
    list->head = newNode;
}

void removeElement(ImageList* list, const char* filename) {
    Node* current = list->head;
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->filename, filename) == 0) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }

    fprintf(stderr, "Erro: O arquivo %s nao foi encontrado na lista\n", filename);
}

void printList(ImageList* list) {
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    if (list->head == NULL) {
        printf("Lista vazia\n");
        return;
    }

    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->filename, ptr1->next->filename) > 0) {
                // Trocar os nós
                char temp[50];
                strcpy(temp, ptr1->filename);
                strcpy(ptr1->filename, ptr1->next->filename);
                strcpy(ptr1->next->filename, temp);
                swapped = 1;
            }

            ptr1 = ptr1->next;
        }

        lptr = ptr1;
    } while (swapped);

    printf("Lista de imagens em ordem alfabetica:\n");
    Node* current = list->head;
    while (current != NULL) {
        printf("%s\n", current->filename);
        current = current->next;
    }
}

void freeList(ImageList* list) {
    Node* current = list->head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int main() {
    ImageList* myList = createList("baboon.pgm");

    insertElement(myList, "barbara.pgm");
    insertElement(myList, "image3.png");

    insertElement(myList, "exemplo.pgm");

    printList(myList);

    removeElement(myList, "barbara.pgm");

    printList(myList);
    
    freeList(myList);

    return 0;
}
