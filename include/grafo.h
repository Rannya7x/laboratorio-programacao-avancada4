#ifndef GRAFO_H
#define GRAFO_H
#include "stdbool.h"
#include "lista_vizinhos.h"

struct no_t {
    int id;
    double pos_x;
    double pos_y;
    lista_vizinhos_t *lista_vizinhos;
    bool pacote_enviado; 
};

typedef struct no_t no_t;
typedef no_t* grafo_t; 

grafo_t grafo_criar(int tam);
void grafo_atualizar_vizinhos(int tam, double raio_comunicacao, grafo_t grafo);
void grafo_destruir(grafo_t grafo, int tam);
lista_vizinhos_t* grafo_obter_vizinhos(grafo_t grafo, int id);
bool* grafo_pacote_enviado(grafo_t grafo, int id);
#endif