# laboratorio-programacao-avancada4

## 1. Objetivo

Mostrar a execução e funcionamento do algoritmo de rede “Flooding” através da implementação de um Simulador por Eventos Discretos.

## 2. Estrutura de Dados

O projeto utiliza uma combinação de estruturas estáticas e dinâmicas para representar a rede e a linha do tempo da simulação.

### 2.1 O Grafo

Representado por uma lista de adjacência, onde a rede é um vetor de nós (`no_t`). Cada nó armazena seu ID, coordenadas (X, Y), uma flag booleana `pacote_enviado` e um ponteiro para sua lista de vizinhos.


### 2.2 A Lista de Nós Vizinhos ao Grafo

Uma lista encadeada simples que armazena apenas os IDs (inteiros) dos nós que estão dentro do raio de comunicação de um nó específico.

```c
struct lista_vizinhos_t{
    int vizinho;
    struct lista_vizinhos_t *proximo;
};
```

### 2.3 A Lista de Eventos

Uma lista encadeada ordenada cronologicamente pelo campo `tempo`. Cada nó da lista aponta para uma estrutura `evento_t`, que contém o tempo da ocorrência, o nó alvo e o tipo do evento.

```c
struct lista_eventos_t {
    evento_t* evento;
    struct lista_eventos_t* proximo_evento;
};


struct evento_t {
    double tempo;
    int alvo;
    int tipo;

};

```


## 3. O Algoritmo de Rede Flooding

É um algoritmo distribuído onde um nó inicial (Nó 0) envia um pacote via broadcast para todos os seus vizinhos. Ao receber um pacote, cada nó verifica se já o repassou anteriormente através da flag pacote_enviado:

- Se não repassou: Envia o pacote para todos os seus vizinhos e marca a flag como true.
- Se já repassou: O pacote é simplesmente descartado para evitar loops infinitos na rede.

## 4. Fluxo de Execução e Interface

### 4.1 Parâmetros de Entrada

O programa recebe via linha de comando (`argv[1]`) o caminho para um arquivo de texto contendo as configurações da rede.

### 4.2 Processamento de Arquivo

1. Cabeçalho: Lê o número total de nós e o raio de comunicação.
2. Nós: Lê o ID e as coordenadas X e Y de cada dispositivo, inserindo-os no grafo.
3. Vizinhança: Calcula a distância Euclidiana entre todos os pares de nós; se a distância < raio, eles são conectados no grafo.

### 4.3 Saída de Dados

A saída consiste em logs formatados mostrando o tempo de recebimento e os vizinhos para os quais o pacote está sendo replicado.

Exemplo de entrada: arquivo_teste.in

```
10  38.0
0   6.0   20.5
1   33.4  6.2
...
```

Exemplo de saída:

```bash

[1.000000] Nó 0 recebeu pacote.
    --> Repassando pacote para o nó 2 ...
    --> Repassando pacote para o nó 1 ...
```

## 5. Estrutura do Projeto

- `main.c`: Coordena a leitura do arquivo, inicializa o grafo, agenda o primeiro evento e dispara a simulação.
- `grafo.c`: Implementa a criação do grafo, atualização de vizinhos por distância e a destruição da estrutura.
- `lista_vizinhos.c`: Gerencia a lista encadeada de IDs que representa as adjacências de cada nó.
- `evento.c`: Contém as funções de criação de eventos e a lógica de inserção ordenada na lista.
- `grafo.h / lista_vizinhos.h / evento.h`: os arquivos de cabeçalho (.h) para garantir a modularização e visibilidade das structs.
- `makefile`: Automatiza a compilação vinculando a biblioteca matemática (`-lm`) e os diretórios de inclusão (`-Iinclude`).

## 6. Requisitos funcionais

Eventos:

`criar_evento`: Aloca e inicializa um novo evento com tempo, alvo e tipo. 
`eventos_comparar`: Função auxiliar para determinar a ordem cronológica entre dois eventos.
`lista_eventos_adicionar_ordenado`: Insere um evento na lista mantendo a ordem crescente de tempo.

Lista de Vizinhos:

`lista_vizinhos_adicionar` : Insere um novo ID de vizinho no início da lista de adjacência.
`lista_vizinhos_destruir`: Libera a memória alocada para a lista de vizinhos de um nó.

Grafo:
`grafo_criar`: Aloca o vetor de nós que compõe a rede.
`grafo_atualizar_vizinhos`: Popula as listas de adjacência comparando a distância entre todos os nós.
`grafo_destruir`: Libera toda a memória do grafo e de suas listas internas.
`grafo_obter_vizinhos`: Retorna o ponteiro para a lista de vizinhos de um nó específico.
`grafo_pacote_enviado`: Retorna o estado da flag de broadcast do nó.


Main:

`simulacao_iniciar`: Executa o loop principal (pega, remove, executa) até que a lista de eventos esteja vazia.


## 7. Como compilar

Para compilar o projeto, utilize o comando:

```bash
make
```
Isso vai gerar o arquivo `programa`

### 7.1 Execução

```bash
./programa arquivo_teste.in
```

### 7.2 Limpeza

```bash
make clean
```

### 9. Conclusão

O projeto demonstra como a simulação por eventos discretos permite modelar comportamentos complexos de rede de forma determinística e controlada. A modularização em C e o uso de listas encadeadas ordenadas são fundamentais para a eficiência da fila de eventos e a integridade da simulação do algoritmo Flooding.
