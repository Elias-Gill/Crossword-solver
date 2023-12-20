#include "head.h"

// Funcion que se encarga de avisar si es que la matriz solucion es incompleta,
// es decir, todas las palabras ya fueron colocadas, pero aun existen espacios
// en blanco.
int matriz_incompleta(char **matriz, int filas, int columnas) {
  for (int i = 0; i < filas; i++) {
    for (int k = 0; k < columnas; k++) {
      if (matriz[i][k] == '_') {
        printf("\nEl crucigrama esta resuelto pero las palabras que ingresaste "
               "no completan el tablero\n");
        return 0;
      }
    }
  }
  return 1;
}

// La funcion principal recursiva.
// NOTA: la variable palabras_colocadas sirve, posiblemente, porque el
// compilador esta optimizando el codigo, entonces, si se borra, el compilador
// optimiza y no se ejecuta como debe.
int resolver_crucigrama(char **matrix, int filas, int columnas,
                        char palabras[][MAX_WORD_LEN], int cant_palabras,
                        Localizacion *palabras_colocadas, int pal_actual) {

  // Todas las palabras ya fueron insertadas. Esta es nuestra condicion de
  // salida: Habemus solucion!!
  if (pal_actual == cant_palabras) {
    imprimir_matriz(filas, columnas, matrix);
    matriz_incompleta(matrix, filas, columnas);
    return 1;
  }

  // probar cada palabra restante con cada fila y columna de la matriz
  // por cada fila y columna de la matriz
  for (int x = 0; x < filas; ++x) {
    for (int y = 0; y < columnas; ++y) {

      // --- Revisar si se puede insertar horizontalmente ---
      if (palabra_cabe(matrix, filas, columnas, palabras[pal_actual], x, y,
                       HORIZONTAL)) {

        // Insertamos la palabar y tratamos de continuar recursivamente
        // con la siguiente palabra en la lista
        cargar_palabra(matrix, filas, columnas, palabras[pal_actual], x, y,
                       HORIZONTAL);
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
      if (palabra_cabe(matrix, filas, columnas, palabras[pal_actual], x, y,
                       VERTICAL)) {

        // Insertar la palabra y continuar recursivamente
        cargar_palabra(matrix, filas, columnas, palabras[pal_actual], x, y,
                       VERTICAL);
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
  char dir_arch_tablero[] = "pruebas/tablero.txt";
  char dir_arch_palabras[] = "pruebas/palabras.txt";

  // Variables
  char **matrix = NULL;
  int filas = 0, columnas = 0;
  char palabras[MAX_WORDS][MAX_WORD_LEN];
  int cant_pals = 0;
  Localizacion var_especial[MAX_WORDS];

  // Cargar el tablero y la lista de palabras
  if (!cargar_tablero(dir_arch_tablero, &matrix, &filas, &columnas)) {
    printf("Error cargando el archivo tablero.txt .\n");
    return 1;
  }
  if (!cargar_lista_palabras(dir_arch_palabras, palabras, &cant_pals)) {
    printf("Error cargando el archivo palabras.txt .\n");
    free(matrix);
    return 1;
  }

  // Resolver e imprimir la solucion
  printf("Resolviendo...\n");
  if (resolver_crucigrama(matrix, filas, columnas, palabras, cant_pals,
                          var_especial, 0)) {
    printf("Solucion encontrada!!!\n");
  } else {
    printf("No existe solucion :( .\n");
  }

  // Liberar la memoria
  for (int i = 0; i < filas; ++i) {
    free(matrix[i]);
  }
  free(matrix);

  return 0;
}
