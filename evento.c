#include "stdbool.h"
#include "stdlib.h"
#include "evento.h"

struct evento_t {
    double tempo;
    int alvo;
    int tipo;

};
typedef struct lista_eventos_t {
    evento_t* evento;
    struct lista_eventos_t* proximo_evento;
} lista_eventos_t;

evento_t* criar_evento(double tempo, int alvo, int tipo) {
    evento_t* novo_evento = (evento_t*)malloc(sizeof(evento_t));
    if (novo_evento == NULL) {
        return NULL;
    }
    novo_evento->tempo = tempo;
    novo_evento->alvo = alvo;
    novo_evento->tipo = tipo;

    return novo_evento;
}

int eventos_comparar(double tempo1, double tempo2) {
    if (tempo1 < tempo2) return -1;
    else if (tempo1 > tempo2) return 1;
    else return 0;
}

bool lista_eventos_adicionar_ordenado(evento_t* evento, lista_eventos_t** lista) {
    evento_t* novo_evento = criar_evento(evento->tempo, evento->alvo, evento->tipo);

    if (novo_evento == NULL) {
        return false;
    };

    lista_eventos_t* nova_lista = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));

    if (nova_lista == NULL) {
        free(novo_evento);
        return false;
    }

    nova_lista->evento = novo_evento;

    //lista vazia ou novo_evento é menor que o primeiro da lista
    if(*lista == NULL || eventos_comparar(novo_evento->tempo, (*lista)->evento->tempo)<0) {
        nova_lista->proximo_evento = *lista;
        *lista = nova_lista;
        return true;
    }

    //ponteiro caminhante
    lista_eventos_t* atual = *lista;
    while(atual->proximo_evento != NULL && eventos_comparar(atual->proximo_evento->evento->tempo, novo_evento->tempo)<0) {
        atual = atual->proximo_evento;
    }

    //Insere novo evento entre atual e atual->proximo_evento
    nova_lista->proximo_evento = atual->proximo_evento;
    atual->proximo_evento = nova_lista;
    
    return true;

}