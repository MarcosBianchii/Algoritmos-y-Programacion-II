VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CFLAGS_ESCAPE =-g -std=c99 -Wall -Wtype-limits -pedantic -Werror
CC = gcc

all: valgrind-pruebas

escape: src/*.c escape_pokemon.c
	$(CC) $(CFLAGS_ESCAPE) src/*.c escape_pokemon.c -o escape 2>&1

valgrind-escape: escape ejemplo/objetos.txt ejemplo/interacciones.txt
	valgrind $(VALGRIND_FLAGS) ./escape ejemplo/objetos.txt ejemplo/interacciones.txt 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas 2>&1

valgrind-pruebas: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1
