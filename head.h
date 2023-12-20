#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100   // adjust this based on actual word list size
#define MAX_WORD_LEN 20 // adjust this based on longest word

//
#define HORIZONTAL 1
#define VERTICAL 0

typedef struct Location {
    int row;
    int col;
} Location;

void imprimir_matriz(int rows, int cols, char **matrix);

int cargar_tablero(char filename[], char ***matrix, int *rows, int *cols);

int cargar_lista_palabras(char filename[], char words[][MAX_WORD_LEN], int *wordCount);

int palabra_cabe(char **matrix, int rows, int cols, char *word, int x, int y,
                 int horizontal);

void cargar_palabra(char **matrix, int rows, int cols, char *word, int x, int y,
        int horizontal);
