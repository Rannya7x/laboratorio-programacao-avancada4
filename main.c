#include <stdio.h>
#include <stdlib.h>
#include "include/grafo.h"
#include "include/lista_vizinhos.h"

int main (int argc, char **argv[]) {
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
    

    return 0;
}