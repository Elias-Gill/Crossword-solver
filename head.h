#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100   
#define MAX_WORD_LEN 20 

//
#define HORIZONTAL 1
#define VERTICAL 0

typedef struct Location {
    int filas;
    int columnas;
} Localizacion;

void imprimir_matriz(int filas, int columnas, char **matrix);

int cargar_tablero(char archivo[], char ***matrix, int *filas, int *columnas);

int cargar_lista_palabras(char archivo[], char palabras[][MAX_WORD_LEN], int *contador);

int palabra_cabe(char **matrix, int filas, int columnas, char *palabra, int x, int y,
                 int horizontal);

void cargar_palabra(char **matrix, int filas, int columnas, char *palabra, int x, int y,
        int horizontal);
