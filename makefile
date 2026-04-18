# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -Iinclude
LIBS = -lm

# Lista de arquivos objeto (gerados a partir dos .c)
OBJ = main.o grafo.o evento.o lista_vizinhos.o
TARGET = programa

# Regra principal: Gera o executável final
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Regras para compilar cada arquivo .c em um .o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

grafo.o: grafo.c
	$(CC) $(CFLAGS) -c grafo.c

evento.o: evento.c
	$(CC) $(CFLAGS) -c evento.c

lista_vizinhos.o: lista_vizinhos.c
	$(CC) $(CFLAGS) -c lista_vizinhos.c

# Regra para limpar os arquivos gerados
clean:
	rm -f *.o $(TARGET)