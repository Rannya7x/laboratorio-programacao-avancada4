#ifndef LISTA_VIZINHOS_H
#define LISTA_VIZINHOS_H
#include "stdbool.h"
struct lista_vizinhos_t{
    int vizinho;
    struct lista_vizinhos_t *proximo;
};
typedef struct lista_vizinhos_t lista_vizinhos_t;
bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista);
void lista_vizinhos_imprimir(lista_vizinhos_t *lista);
void lista_vizinhos_destruir(lista_vizinhos_t **lista);
#endif
