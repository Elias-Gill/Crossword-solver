# Implementacion

Esta es una implementacion en lenguaje C del juego de crucigrama. Para este problema se cuentan con dos archivos de texto. El primero, el cual contiene el tablero
del juego, el segundo el cual contendra las palabras con las cuales se debe resolver el crucigrama (el algoritmo lo que hace es ubicar dichas palabras). 

El tablero del crucigrama se representa mediante "*" para casillas ocupadas y "_" para espacios de letras, ademas, la primera linea del archivo de texto cuenta con 
las dimensiones del tablero "largo" y "ancho".

El segundo archivo de texto contiene las palabras que son solucion del crucigrama, listadas una por linea. El programa no resuelve el crucigrama desde 0, es requerido que
se proporcionen las palabras que pueden ser solucion del crucigrama.

Ojala a alguien le sirva.

# Funcionamiento

El algoritmo de resolucion es bastante simple. Este se basa en fuerza bruta utilizando "[backtracking](https://es.wikipedia.org/wiki/Vuelta_atr%C3%A1s)", la cual consiste
en realizar una seria de llamadas recursivas a una funcion, y si dicho camino escogido no resulta ser solucion,
entonces se vuelve a un estado anterior para posteriormente tomar un camino distinto.

## Partes esenciales

### Condicion de parada

Nuestra condicion de parada es cuando todas las palabras fueron insertadas, o cuando ya no se puedan insertar mas palabras en el tablero.

### Llamada recursiva

Los pasos de nuestras llamadas recursivas son:

- Comprobar todas las celdas de la matriz para ver si una palabra puede insertarse dicha celda inicial
- En caso de poder insertarse, entonces procede a insertar dicha palabra
- Luego realiza una llamada recursiva pero pasando como parametro la siguiente palabra de la lista
- En caso de no poder insertar ni en vertical ni en horizontal en ningun caso, entonces se termina de buscar por ese camino retornando un 0.
