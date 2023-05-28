#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grafo.h"
#include "meios.h"
#include "cliente.h"


// dijkstras algorithm permite nos encontrar o caminho mais curto entre 2 vertices

int main() {

    struct dadosMeios* Meios = NULL;
    struct dadosClientes* Clientes = NULL;
    struct grafo* Grafo = NULL;

    lerFicheiroMeios(&Meios);
    lerFicheiroClientes(&Clientes);
    lerFicheiroArestas(&Grafo);

    struct grafo* nodo = Grafo;
    while(nodo!=NULL){

        printf("%d;%s;%d;%.2f;%d;%s", nodo->meios->idMeios,nodo->meios->meios,nodo->meios->bateria,nodo->meios->preco,nodo->meios->autonomia,nodo->meios->localizacao);
        nodo=nodo->seguinte;
    } 

    MostraGrafo(Grafo);

    listarMeioRaio(Grafo,Clientes,Meios,"Jorge",10000, "carro");



    return 0;
}