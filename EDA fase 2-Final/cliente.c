#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grafo.h"
#include "cliente.h"

/**
 * @brief funcao de leitura do ficheiro dos clientes
 * id;nome;nif;morada;localizacao
 * 
 * @param Cliente 
 */

void lerFicheiroClientes(struct dadosClientes** Cliente) {
    FILE* file;

    file = fopen("dados Cliente.bin","rb");

    if (file == NULL) {
        printf("Erro na abertura do ficheiro");
        exit(1);
    }

    struct dadosClientes* anterior = NULL;
    char linha[100];
    char *token;

    while (fgets(linha, sizeof(linha), file) != NULL) {

        struct dadosClientes* nodo = malloc(sizeof(struct dadosClientes));
        

        token = strtok(linha, ";");
        nodo->id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(nodo->Nome, token);

        token = strtok(NULL, ";");
        nodo->saldo = atof(token);

        token = strtok(NULL, ";");
        nodo->Nif = atoi(token);

        token = strtok(NULL, ";");
        strcpy(nodo->morada, token);

        token = strtok(NULL, ";");
        strcpy(nodo->localizacaoCliente, token);

        nodo->seguinte = NULL;

        if (anterior == NULL) {
            *Cliente = nodo;
        } else {
            anterior->seguinte = nodo;
        }
        anterior = nodo;
    }

    fclose(file);
}