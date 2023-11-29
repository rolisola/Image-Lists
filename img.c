#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "img.h"

// Lê imagem de um arquivo
imgb read_img(FILE *fimg){
    // Tipo de imagem. Vamos fixar essa linha como "P2"
    char ver[5];
    fscanf(fimg, "%s", ver);

    // Dimensões da imagem
    imgb I;
    fscanf(fimg, "%d ", &I.h);
    fscanf(fimg, "%d ", &I.w);
    fscanf(fimg, "%d ", &I.cinza);

    I.pixel = malloc(I.h * I.w * sizeof(int));
    if (I.pixel != NULL){
        for (int i = 0; i < I.h; i++){
            for (int j = 0; j < I.w; j++){
                fscanf(fimg, "%d ", &I.pixel[i * I.w + j]);
            }
        }
    } else{
        printf("Falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    return I;
}

// Libera memória em imgb
void free_imgb(imgb *I){
    if (I->pixel != NULL)
    {
        free(I->pixel);
        I->pixel = NULL;
    }
}

// Aplica limiarização a cada pixel
void limiar(imgb *I, int lim){
    if (I->pixel != NULL){
        for (int i = 0; i < I->h; i++){
            for (int j = 0; j < I->w; j++){
                if (I->pixel[i * I->w + j] < lim){
                    I->pixel[i * I->w + j] = 0;
                } else {
                    I->pixel[i * I->h + j] = I->cinza;
                }
            }
        }
    } else{
        printf("Imagem de entrada é NULL.");
        exit(EXIT_FAILURE);
    }
}

// Aplica a inversao de cada pixel
void inversa(imgb *I){
    if (I->pixel != NULL){
        for (int i = 0; i < I->h; i++){
            for (int j = 0; j < I->w; j++){
                I->pixel[i * I->w + j] = (I->cinza) - (I->pixel[i * I->w + j]);
            }
        }
    } else{
        printf("Imagem de entrada é NULL.");
        exit(EXIT_FAILURE);
    }
}

// Escreve imgb a um arquivo com nome filename
void write_imgb(char *filename, imgb *I){
    FILE *fp = fopen(filename, "w");
    if (fp != NULL){
        if (I->pixel != NULL){
            // Informações de cabeçalho
            fprintf(fp, "P2\n");
            fprintf(fp, "%d %d \n", I->h, I->w);
            fprintf(fp, "%d \n", I->cinza);

            // Dados dos pixels
            for (int i = 0; i < I->h; i++){
                for (int j = 0; j < I->w; j++){
                    fprintf(fp, "%d ", I->pixel[i * I->w + j]);
                }
                fprintf(fp, "\n");
            }
        } else{
            printf("Imagem de entrada é NULL. \n");
            exit(EXIT_FAILURE);
        }
    } else{
        printf("Não foi possível criar arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }
}
