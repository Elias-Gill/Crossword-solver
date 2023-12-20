#include "head.h"

// la funcion principal.
// NOTE: la variable palabras_colocadas sirve como reserva de memoria del stack
// entre funciones (creo)
int resolver_crucigrama(char **matrix, int filas, int columnas,
                        char palabras[][MAX_WORD_LEN], int cant_palabras,
                        Location *palabras_colocadas, int pal_actual) {

    // Todas las palabras ya fueron insertadas. Esta es nuestra condicion de
    // salida: Habemus solucion!!
    if (pal_actual == cant_palabras) {
        imprimir_matriz(filas, columnas, matrix);
        return 1;
    }

    // probar cada palabra restante con cada fila y columna de la matriz
    // por cada fila y columna de la matriz
    for (int x = 0; x < filas; ++x) {
        for (int y = 0; y < columnas; ++y) {

            // --- Revisar si se puede insertar horizontalmente ---
            if (palabra_cabe(matrix, filas, columnas, palabras[pal_actual], x,
                             y, HORIZONTAL)) {

                // Insertamos la palabar y tratamos de continuar recursivamente
                // con la siguiente palabra en la lista
                cargar_palabra(matrix, filas, columnas, palabras[pal_actual], x,
                               y, HORIZONTAL);
                if (resolver_crucigrama(matrix, filas, columnas, palabras,
                                        cant_palabras, palabras_colocadas,
                                        pal_actual + 1)) {
                    return 1;
                }

                // Si llegamos aca significa que esta no parece ser una
                // solucion, por tanto devolvemos la matriz al estado anterior.
                char aux[strlen(palabras[pal_actual])];
                for (size_t z = 0; z < strlen(palabras[pal_actual]); z++) {
                    aux[z] = '_';
                }
                cargar_palabra(matrix, filas, columnas, aux, x, y, HORIZONTAL);
            }

            // --- Lo mismo pero en vertical ---
            if (palabra_cabe(matrix, filas, columnas, palabras[pal_actual], x,
                             y, VERTICAL)) {

                // Insertar la palabra y continuar recursivamente
                cargar_palabra(matrix, filas, columnas, palabras[pal_actual], x,
                               y, VERTICAL);
                if (resolver_crucigrama(matrix, filas, columnas, palabras,
                                        cant_palabras, palabras_colocadas,
                                        pal_actual + 1)) {
                    return 1;
                }

                // backtrack en caso de fallar
                char aux[strlen(palabras[pal_actual])];
                for (size_t z = 0; z < strlen(palabras[pal_actual]); z++) {
                    aux[z] = '_';
                }
                cargar_palabra(matrix, filas, columnas, aux, x, y, VERTICAL);
            }
        }
    }

    // En caso de no poder insertar la palabra significa que este camino no
    // tiene solucion. Retornamos 0 (falso)
    return 0;
}

int main() {
    // DIrecciones de los archivos
    char matrixFilepath[] = "pruebas/tablero.txt";
    char wordsFilepath[] = "pruebas/palabras.txt";

    // Variables
    char **matrix = NULL;
    int rows = 0, cols = 0;
    char words[MAX_WORDS][MAX_WORD_LEN];
    int wordCount = 0;
    Location placedWords[MAX_WORDS];

    // Cargar el tablero y la lista de palabras
    if (!cargar_tablero(matrixFilepath, &matrix, &rows, &cols)) {
        printf("Error loading matrix file.\n");
        return 1;
    }
    if (!cargar_lista_palabras(wordsFilepath, words, &wordCount)) {
        printf("Error loading word list file.\n");
        free(matrix);
        return 1;
    }

    // Resolver e imprimir la solucion
    printf("Solving...\n");
    if (resolver_crucigrama(matrix, rows, cols, words, wordCount, placedWords,
                            0)) {
        printf("Solution found!\n");
    } else {
        printf("No solution found.\n");
    }

    // Liberar la memoria alocada
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
