#ifndef LISTA_DINAMICA_H_INCLUDED
#define LISTA_DINAMICA_H_INCLUDED

typedef struct node {
    char filename[50];
    struct node* next;
} node;

typedef struct imglist{
    node* head;
} imglist;

node* alloc_element();
imglist* create_list(char* filename);
void insert_element(imglist* list, char* filename);
void remove_element(imglist* list, char* filename);
void print_list(imglist* list);
void save_list_file(imglist* list, char* filename);
imglist* load_list(char* filename);
void free_list(imglist* list);

#endif // LISTA_DINAMICA_H_INCLUDED
