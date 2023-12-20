# Implementacion

Esta es una implementacion en lenguaje C del juego de crucigrama.
Ojala a alguien le sirva y no tenga que sufrir con esta cosa asquerosa.

# Funcionamiento

El algoritmo de resolucion es bastante simple y se basa en una tecnica llamda "[backtracking](https://es.wikipedia.org/wiki/Vuelta_atr%C3%A1s)", la cual consiste
en realizar una seria de llamadas recursivas a una funcion, y si dicho camino escogido no resulta ser solucion,
entonces se vuelve a un estado anterior para posteriormente tomar un camino distinto.

Asi suscesivamente hasta recorrer todos lo caminos o encontrar una solucion.

## Partes esenciales

### Condicion de parada

Nuestra condicion de parada es cuando todas las palabras fueron insertadas, o cuando ya no se puedan insertar mas palabras en el tablero.

### Llamada recursiva

Los pasos de nuestras llamadas recursivas son:

- Comprobar todas las celdas de la matriz para ver si una palabra puede insertarse dicha celda inicial
- En caso de poder insertarse, entonces procede a insertar dicha palabra
- Luego realiza una llamada recursiva pero pasando como parametro la siguiente palabra de la lista
- En caso de no poder insertar ni en vertical ni en horizontal en ningun caso, entonces se termina de buscar por ese camino retornando un 0.

# WebGrafia:
- https://iq.opengenus.org/crossword-using-backtracking/
