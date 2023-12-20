#include "head.h"

void imprimir_matriz(int filas, int columnas, char **matrix) {
    // Loop through each row and column
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Print the current character with a space afterwards
            printf("%c  ", matrix[i][j]);
        }
        // Print a newline at the end of each row
        printf("\n");
    }
}

int cargar_tablero(char archivo[], char ***matrix, int *filas, int *columnas) {
    // abrir el archivo de tablero
    FILE *file = fopen(archivo, "r");
    if (!file) {
        return 0;
    }

    // leer el tamano de la matriz
    fscanf(file, "%d %d", filas, columnas);
    *matrix = (char **)malloc((*filas) * sizeof(char *));

    // cargar el tablero leyendo caracter por caracter
    for (int i = 0; i < *filas; ++i) {
        (*matrix)[i] = (char *)malloc((*columnas) * sizeof(char));
        fscanf(file, "%s", (*matrix)[i]);
    }

    fclose(file);

    return 1;
}

int cargar_lista_palabras(char archivo[], char palabras[][MAX_WORD_LEN],
                          int *wordCount) {
    // abrir el archivo
    FILE *file = fopen(archivo, "r");
    if (!file) {
        return 0;
    }

    /* contar la cantidad de palabras e ir guardando en el arreglo de palabras
    El arreglo de palabras admite un maximo de 100 palabras de 20 letras por
    palabra */
    *wordCount = 0;
    while (fscanf(file, "%s", palabras[*wordCount]) != EOF) {
        (*wordCount)++;
    }

    fclose(file);

    return 1;
}

// Esta funcion determina si una palabra cabe de forma vertical u horizontal
// (depende del parametro "horizontal"). Retorna verdadero o falso
int palabra_cabe(char **matrix, int rows, int cols, char *word, int x, int y,
                 int horizontal) {
    if (horizontal) {
        for (int i = 0; i < strlen(word); ++i) {
            if (y + i >= cols ||
                (matrix[x][y + i] != '_' && matrix[x][y + i] != word[i])) {
                return 0;
            }
        }
    } else { // vertical
        for (int i = 0; i < strlen(word); ++i) {
            if (x + i >= rows ||
                (matrix[x + i][y] != '_' && matrix[x + i][y] != word[i])) {
                return 0;
            }
        }
    }
    return 1;
}

// Carga una palabra en una posicion de la matriz (para llamar a esta funcion si
// o si se debe llamar antes a "palabra_cabe")
void cargar_palabra(char **matrix, int rows, int cols, char *word, int x, int y,
                    int horizontal) {
    if (horizontal) {
        for (int i = 0; i < strlen(word); ++i) {
            matrix[x][y + i] = word[i];
        }
    } else {
        for (int i = 0; i < strlen(word); ++i) {
            matrix[x + i][y] = word[i];
        }
    }
}
