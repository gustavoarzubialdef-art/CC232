# Diseño de la solución

## Problema
Dado un arreglo `nums` y un tamaño de ventana `k`, se requiere calcular el valor máximo de cada subarreglo contiguo de longitud `k` conforme la ventana se desliza hacia la derecha.

## Estructura usada
La solución utiliza un `std::deque<int>` que almacena índices de `nums`.

## Invariante
En cada paso, la cola mantiene los índices de la ventana actual en orden decreciente según el valor correspondiente en `nums`.
El índice al frente de la cola corresponde al mayor valor de la ventana.

## Operación principal
Para cada nuevo elemento `nums[i]`:
- Se eliminan los índices que ya no pertenecen a la ventana actual (`i - k`).
- Se eliminan desde el extremo posterior todos los índices con valores menores que `nums[i]`.
- Se agrega el índice actual al final de la cola.
- Si `i >= k - 1`, se registra el valor en el frente como máximo de la ventana.

## Complejidad
- Tiempo: O(n), ya que cada índice entra y sale de la `deque` a lo más una vez.
- Espacio: O(n) en el peor caso debido al vector de resultados y a la `deque`.