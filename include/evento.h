#ifndef EVENTO_H
#define EVENTO_H
typedef struct evento_t evento_t;
typedef struct lista_eventos_t lista_eventos_t;
evento_t* criar_evento(double tempo, int alvo, int tipo);
int eventos_comparar(double tempo1, double tempo2);
bool lista_eventos_adicionar_ordenado(evento_t* evento, lista_eventos_t** lista);
#endif
