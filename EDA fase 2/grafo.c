#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "meios.h"
#include "cliente.h"

struct arestas* createAresta(int origem, int destino, float distancia) {
    struct arestas* nova_aresta = malloc(sizeof(struct arestas));
    
    if (nova_aresta == NULL) {
        return NULL;
    }
    
    nova_aresta->origem = origem;
    nova_aresta->destino = destino;
    nova_aresta->distancia = distancia;
    nova_aresta->seguinte = NULL;
    
    return nova_aresta;
}

void insertAresta(struct grafo* g, int origem, int destino, float distancia) {
    struct grafo* aux = g;
    
    while (aux != NULL && aux->meios->idMeios != origem) {
        aux = aux->seguinte;
    }
    
    if (aux != NULL) {
        struct arestas* nova_aresta = createAresta(origem, destino, distancia);
        
        if (aux->arestas == NULL) {
            aux->arestas = nova_aresta;
        } else {
            struct arestas* aresta_atual = aux->arestas;
            
            while (aresta_atual->seguinte != NULL) {
                aresta_atual = aresta_atual->seguinte;
            }
            
            aresta_atual->seguinte = nova_aresta;
        }
    }
}

void MostraGrafo(struct grafo* grafos) {
    struct grafo* aux = grafos;

    while (aux != NULL) {
        struct arestas* aresta_atual = aux->arestas;
        
        while (aresta_atual != NULL) {
            printf("Vertice: %d\n", aux->meios->idMeios);
            printf("   Aresta liga: %d -> %d | Distancia: %.2f\n", aux->meios->idMeios, aresta_atual->destino, aresta_atual->distancia);
            aresta_atual = aresta_atual->seguinte;
        }
        
        aux = aux->seguinte;
    }
}

//nesta funcao é suposto enviar um cliente por argumento, percorro a lista dos clientes ate encontrar o cliente
// depois saco a coordenada do cliente, depois percorro o grafo com aquela coordenada e listo os meios no raio

void listarMeioRaio(struct grafo* grafos, struct dadosClientes* Cliente, struct dadosMeios* meios, char nomeCliente[50], float raio, char tipoMeio[50]) {

    struct dadosClientes* novoCliente = Cliente;
    char coordenadaCliente[50];

    while (novoCliente != NULL) {
        if (strcmp(nomeCliente, novoCliente->Nome) == 0) {
            strcpy(coordenadaCliente, novoCliente->localizacaoCliente);
    
            struct dadosMeios* novoMeio = meios;

            while (novoMeio != NULL){
               printf("%s",novoMeio->localizacao);
                if (strcmp(coordenadaCliente, novoMeio->localizacao) == 0) {
                    
                    struct grafo* aux = grafos;
                    
                    while (aux != NULL){
                    
                        struct arestas* novoAresta = aux->arestas;
                        struct dadosMeios* meioDestino = meios;

                        while (novoAresta != NULL && meioDestino != NULL) {
                            
                            if (meioDestino->idMeios == novoAresta->destino) {
                               printf("%d",meioDestino->idMeios);
                                if (strcmp(tipoMeio, novoMeio->meios) == 0 && novoAresta->distancia <= raio){
                                    printf("Meios disponiveis: %s\n", novoMeio->meios);
                                }
                            }
                            meioDestino = meioDestino->seguinte;
                            novoAresta = novoAresta->seguinte;
                        } 
                        aux = aux->seguinte;
                    }
                }
                novoMeio = novoMeio->seguinte;
            }
        }
        novoCliente = novoCliente->seguinte;
    }
}



void lerFicheiroArestas(struct grafo** grafos) {
    FILE* file;
    file = fopen("arestas.bin", "rb");

    if (file == NULL) {
        printf("Erro na abertura do ficheiro");
        exit(1);
    }

    struct grafo* anterior = NULL;
    char linha[100];
    char* token;

    while (fgets(linha, sizeof(linha), file) != NULL) {
        struct grafo* nodo = malloc(sizeof(struct grafo));
        nodo->meios = malloc(sizeof(struct dadosMeios));
        nodo->arestas = NULL;
        
        token = strtok(linha, ";");
        int origem = atoi(token);

        token = strtok(NULL, ";");
        int destino = atoi(token);

        token = strtok(NULL, ";");
        float distancia = atof(token);

        nodo->meios->idMeios = origem;
        
        
        if (anterior == NULL) {
            *grafos = nodo;
        } else {
            anterior->seguinte = nodo;
        }
        
        anterior = nodo;
        insertAresta(*grafos, origem, destino, distancia);
    }
    
    fclose(file);
}