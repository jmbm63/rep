#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "meios.h"
#include "cliente.h"

/**
 * @brief calcular trajeto com  menor distancia para percorrer
 * deve passar em todos os meios cujo bateria seja menor que 50%
 * 
*/

void caxeiroViajante(struct grafo* grafos, struct dadosMeios* meios){

    struct grafo* Grafo=grafos;
    struct dadosMeios* Meios=meios;



}


// percorrer a lista dos meios ate encontrar o meio certo e retirar o id
int meioPretendido(struct dadosMeios* meios, char tipoMeio[50]){

    int id;

    struct dadosMeios* Meios=meios;

    while(Meios!=NULL){
        
        if(strcmp(tipoMeio,Meios->meios)==0){
            id=Meios->idMeios;
        }  
        Meios=Meios->seguinte;
    }
    return id;
}


//nesta funcao é suposto enviar um cliente por argumento, percorro a lista dos clientes ate encontrar o cliente
// depois saco a coordenada do cliente, depois percorro o grafo com aquela coordenada e listo os meios no raio

void listarMeioRaio(struct grafo* grafos, struct dadosClientes* Cliente, struct dadosMeios* meios, char nomeCliente[50], float raio, char tipoMeio[50]) {

    struct dadosClientes* novoCliente = Cliente;
    char coordenadaCliente[50];
   
    while (novoCliente != NULL){ // percorrer lista dos clientes e comparar o nome e retirar a sua localizacao
        
        if (strcmp(nomeCliente, novoCliente->Nome) == 0){
            strcpy(coordenadaCliente, novoCliente->localizacaoCliente);

            struct dadosMeios* novoMeio = meios;

            while (novoMeio != NULL){
               
                if (strcmp(coordenadaCliente, novoMeio->localizacao) == 0){ // encontrar a localizacao do meio em relacao ao cliente
                    
                    struct grafo* aux = grafos; 

                    while(aux!=NULL){ 
                        struct arestas* aresta=aux->arestas;
                        
                        while(aresta!=NULL){
                            
                            if(novoMeio->idMeios==aresta->origem){ // já estou no nodo da localizacao do meio portanto e procurar a origem no grafo
                                // tou na origem
                                
                                //encontrar a/as localizacoes do meio pretendido
                                int id = meioPretendido(meios,tipoMeio);
                                if(id==aresta->destino && aresta->distancia<=raio){
                                   
                                    printf("\nO meio prentendido e:  %s",tipoMeio);
                                    printf("\nDistancia:  %2.f",aresta->distancia); 

                                }else if(aresta->distancia>raio){
                                    printf("\nnao ha meios disponiveis desse tipo");
                                    break;
                                }                        
                            }
                            aresta=aresta->seguinte;
                        }
                        aux=aux->seguinte;
                    }
                }
                novoMeio = novoMeio->seguinte;
            }
        }
        novoCliente = novoCliente->seguinte;
    }
}

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

void MostraGrafo(struct grafo* grafos){
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

void lerFicheiroArestas(struct grafo** grafos){

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

        insertAresta(*grafos, origem, destino, distancia);
        anterior = nodo;   
    }
    fclose(file);
}


