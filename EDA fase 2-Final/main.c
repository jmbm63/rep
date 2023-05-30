#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grafo.h"
#include "meios.h"
#include "cliente.h"

int main() {

    struct dadosMeios* Meios = NULL;
    struct dadosClientes* Clientes = NULL;
    struct grafo* Grafo = NULL;


    lerFicheiroMeios(&Meios);
    lerFicheiroClientes(&Clientes);
    lerFicheiroArestas(&Grafo);

    MostraGrafo(Grafo);
    listarMeioRaio(Grafo,Clientes,Meios,"laura",100,"carro");
    
    return 0;
}