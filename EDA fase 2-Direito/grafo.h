#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
/**
 * @brief Neste ficheiro são implementadas as structs com a informação
 * dos clientes e meios de mobilidade eletrica e o grafo
 * 
 */
struct dadosClientes{ 

    int id; // identificacao do no 
    char Nome[50]; // nome do men
    float saldo; // saldo do cliente
    int Nif;
    char morada[50]; // morada do cliente
    char localizacaoCliente[50];
    
    struct dadosClientes *seguinte;

};

struct dadosMeios{ 

    int idMeios; // identificacao do no 
    char meios[50]; // meio de mobilidade
    int bateria; // bateria do meio
    float preco;
    int autonomia;
    char localizacao[50]; // localizacao do meio de mobilidade

    struct dadosMeios *seguinte;
};

struct arestas{

    float distancia;  // arestas -> Este valor vai ser retidado do ficheiro "arestas.bin"
    
    // variaveis utilizadas para ligar os dois meios atraves de uma aresta
    int origem; // origem
    int destino; // destino
    struct arestas* seguinte;
};


// o numero de arestas devera de ser a distancia
struct grafo{

    struct dadosMeios* meios;
    struct arestas* arestas;
    struct grafo * seguinte;
};


// Funcoes
void listarMeioRaio(struct grafo* grafos, struct dadosClientes* Cliente, struct dadosMeios* meios, char nomeCliente[50], float raio, char tipoMeio[50]);
void lerFicheiroArestas(struct grafo** grafos);
void MostraGrafo(struct grafo* grafos);
