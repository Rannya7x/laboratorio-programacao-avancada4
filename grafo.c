#include "stdbool.h"
#include "stdlib.h"
#include "math.h"
#include "include/grafo.h"
#include "include/lista_vizinhos.h"

grafo_t grafo_criar(int tam) {
    grafo_t grafo = (grafo_t*)malloc(sizeof(no_t) * tam);
    if (grafo == NULL) {
        return NULL;
    }
    for (int i = 0; i < tam; i++) {
        grafo[i].lista_vizinhos = NULL;
        grafo[i].pacote_enviado = false;
    }
    return grafo;
}

void grafo_atualizar_vizinhos(int tam, double raio_comunicacao, grafo_t grafo){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(i != j){
                double distancia = sqrt(pow(grafo[i].pos_x - grafo[j].pos_x, 2) + pow(grafo[i].pos_y - grafo[j].pos_y, 2));
                if(distancia < raio_comunicacao){
                    lista_vizinhos_adicionar(grafo[i].id, &grafo[j].lista_vizinhos);
                }
            }
        }
    }
}

lista_vizinhos_t* grafo_obter_vizinhos(grafo_t grafo, int id){
    return grafo[id].lista_vizinhos;
}

bool* grafo_pacote_enviado(grafo_t grafo, int id){
    return &grafo[id].pacote_enviado;
}

void grafo_destruir(grafo_t grafo, int tam){
    for(int i = 0; i < tam; i++){
        lista_vizinhos_destruir(grafo[i].lista_vizinhos);
    }
    free(grafo);
}