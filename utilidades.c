#include "head.h"

void imprimir_matriz(int filas, int columnas, char **matrix) {
  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      printf("%c  ", matrix[i][j]);
    }
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
  if (*filas > 16 || *columnas > 16)
    return 0;

  // alojar memoria necesaria para la matriz tablero
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
                          int *cant_palabras) {
  // abrir el archivo
  FILE *file = fopen(archivo, "r");
  if (!file) {
    return 0;
  }

  /* contar la cantidad de palabras e ir guardando en el arreglo de palabras
  El arreglo de palabras admite un maximo de 100 palabras de 20 letras por
  palabra */
  *cant_palabras = 0;
  while (fscanf(file, "%s", palabras[*cant_palabras]) != EOF) {
    // revisar que las palabras no pasen de 16 letras
    if (strlen(palabras[*cant_palabras]) > MAX_WORD_LEN) {
      printf("El tablero solo puede ser de maximo 16x16\n");
      return 0;
    }
    (*cant_palabras)++;
  }

  fclose(file);

  return 1;
}

// Esta funcion determina si una palabra cabe de forma vertical u horizontal
// (depende del parametro "horizontal"). Retorna verdadero o falso
int palabra_cabe(char **matrix, int filas, int columnas, char *palabra, int x, int y,
                 int horizontal) {
  if (horizontal) {
    for (int i = 0; i < strlen(palabra); ++i) {
      if (y + i >= columnas ||
          (matrix[x][y + i] != '_' && matrix[x][y + i] != palabra[i])) {
        return 0;
      }
    }
  } else { // vertical
    for (int i = 0; i < strlen(palabra); ++i) {
      if (x + i >= filas ||
          (matrix[x + i][y] != '_' && matrix[x + i][y] != palabra[i])) {
        return 0;
      }
    }
  }
  return 1;
}

// Carga una palabra en una posicion de la matriz (para llamar a esta funcion si
// o si se debe llamar antes a "palabra_cabe")
void cargar_palabra(char **matrix, int filas, int columnas, char *palabras, int x, int y,
                    int horizontal) {
  if (horizontal) {
    for (int i = 0; i < strlen(palabras); ++i) {
      matrix[x][y + i] = palabras[i];
    }
  } else {
    for (int i = 0; i < strlen(palabras); ++i) {
      matrix[x + i][y] = palabras[i];
    }
  }
}
