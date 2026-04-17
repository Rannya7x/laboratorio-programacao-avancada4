#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "include/lista_vizinhos.h"

struct lista_vizinhos_t{
    int vizinho;
    struct lista_vizinhos_t *proximo;
};

bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista){
    lista_vizinhos_t *nova_lista = (lista_vizinhos_t*)malloc(sizeof(lista_vizinhos_t));
    if(nova_lista == NULL) return false;
    nova_lista->vizinho = vizinho;
    nova_lista->proximo = *lista;
    *lista = nova_lista;
    return true;
}

void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
    lista_vizinhos_t *atual = lista;
    while(atual != NULL){
        printf("\t--> Repassando pacote para o nó %d ...\n", atual->vizinho);
        atual = atual->proximo;
    }
}
void lista_vizinhos_destruir(lista_vizinhos_t **lista){
    lista_vizinhos_t *atual = *lista;
    while(atual != NULL){
        lista_vizinhos_t *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    *lista = NULL;
}
