all: main

run: main
	./main

main: matriz_de_adjacencia.o main.o
	gcc matriz_de_adjacencia.o main.o -o main

main.o: main.c
	gcc main.c -c

matriz_de_adjacencia.o: matriz_de_adjacencia.c
	gcc matriz_de_adjacencia.c -c