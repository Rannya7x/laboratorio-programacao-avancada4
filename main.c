#include <stdio.h>
#include <stdlib.h>
#include "include/grafo.h"
#include "include/lista_vizinhos.h"
#include "include/evento.h"

void simulacao_iniciar(lista_eventos_t **lista_eventos, grafo_t grafo){
    while(*lista_eventos != NULL){
        //Salva evento atual
        evento_t* evento_atual = (*lista_eventos)->evento;
        lista_eventos_t* no_lista = *lista_eventos;

        //Remove da lista
        *lista_eventos = (*lista_eventos)->proximo_evento;

        //Executa o evento
        printf("[%3.6f] Nó %d recebeu pacote.\n", evento_atual->tempo, evento_atual->alvo);

        if (grafo[evento_atual->alvo].pacote_enviado == false) {
            grafo[evento_atual->alvo].pacote_enviado = true;
            
            // Obtém vizinhos e gera novos eventos
            lista_vizinhos_t* atual_vizinho = grafo[evento_atual->alvo].lista_vizinhos;
            while (atual_vizinho != NULL) {
                // Imprime log de repasse ANTES de criar o evento
                printf("\t--> Repassando pacote para o nó %d ...\n", atual_vizinho->vizinho);
                
                // Fórmula de tempo determinística 
                double novo_tempo = evento_atual->tempo + (0.1 + (atual_vizinho->vizinho * 0.01));
                
                evento_t* novo_evento = criar_evento(novo_tempo, atual_vizinho->vizinho, 1);
                lista_eventos_adicionar_ordenado(novo_evento, lista_eventos);
                
                atual_vizinho = atual_vizinho->proximo; 
            }
        }

        free(evento_atual);
        free(no_lista);
    }
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    int num_nos;
    double raio_comunicacao;
    fscanf(arquivo, "%d\t%lf\n", &num_nos, &raio_comunicacao);

    // Criar o grafo
    grafo_t grafo = grafo_criar(num_nos);

    for (int i = 0; i < num_nos; i++) {
        fscanf(arquivo, "%d\t%lf\t%lf\n", &grafo[i].id, &grafo[i].pos_x, &grafo[i].pos_y);
        grafo[i].lista_vizinhos = NULL;
        grafo[i].pacote_enviado = false;
    }
    fclose(arquivo);

    // Atualizar as listas de vizinhos
    grafo_atualizar_vizinhos(num_nos, raio_comunicacao, grafo);

    //Configura o primeiro evento
    lista_eventos_t *lista_eventos = NULL;
    evento_t* primeiro_evento = criar_evento(1.0, 0, 1);
    lista_eventos_adicionar_ordenado(primeiro_evento, &lista_eventos);
    simulacao_iniciar(&lista_eventos, grafo);
    grafo_destruir(grafo, num_nos);
    
    return 0;
}