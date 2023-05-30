#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "meios.h"


/**
 * @brief funcao de leitura dos meios de mobilidade presentes
 * id;tipo de meio ; bateria ; preco ; autonomia ; localizacao
 * 
 * @param meios 
 */

void lerFicheiroMeios(struct dadosMeios** meios){
    FILE* file;

    file = fopen("dados Meios.bin", "rb");

    if (file == NULL) {
        printf("Erro na abertura do ficheiro");
        exit(1);
    }

    struct dadosMeios* anterior = NULL;
    char linha[100];
    char *token;

    while (fgets(linha, sizeof(linha), file) != NULL) {

        struct dadosMeios* nodo = malloc(sizeof(struct dadosMeios));
        token = strtok(linha, ";");
        nodo->idMeios = atoi(token);
        
        token = strtok(NULL, ";");
        strcpy(nodo->meios, token);

        token = strtok(NULL, ";");
        nodo->bateria = atoi(token);
        
        token = strtok(NULL, ";");
        nodo->preco = atof(token);

        token = strtok(NULL, ";");
        nodo->autonomia = atoi(token);

        token = strtok(NULL, ";");
        strcpy(nodo->localizacao, token);

        nodo->seguinte = NULL;

        if (*meios == NULL) {
            *meios = nodo;
        } else {
            anterior->seguinte = nodo;
        }
        anterior = nodo;
    }

    fclose(file);
}


