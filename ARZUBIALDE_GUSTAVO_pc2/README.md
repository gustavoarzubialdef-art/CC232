# PC2 - CC232

## Estudiante
- Nombre: Gustavo Anthony Arzubialde Fierro
- Código: 20230205H
- Problema asignado: LeetCode 239 - Sliding Window Maximum
- Enlace: https://leetcode.com/problems/sliding-window-maximum/

## Referencia oficial
- Archivo de asignación:
  https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv

## Tema principal
- Semana: 3
- Estructura o técnica principal: Deque monótona / ventana deslizante

## Resumen de la solución
La solución mantiene una deque de índices que representa una ventana deslizante de tamaño `k`.
La deque es monótona decreciente: el frente siempre guarda el índice del valor máximo actual.
Al avanzar la ventana, se eliminan índices que salen de rango y se descartan valores menores desde atrás.

## Complejidad
- Tiempo: O(n)
- Espacio: O(n) en el peor caso, con uso adicional de deque y resultado.

## Invariante o idea clave
La deque mantiene índices de elementos en orden decreciente por valor.
Dentro de la ventana actual, cualquier índice en la deque tiene un valor estrictamente mayor que los índices que le siguen.

## Archivos relevantes
- include/sliding_window_maximum.h
- src/main.cpp
- tests/test_sliding_window_maximum.cpp

## Compilación
```bash
cd Practicas/Practica2_CC232
cmake -S . -B build
cmake --build build
```

## Ejecución
```bash
./build/sliding_window_maximum
```

## Casos de prueba
1. `nums = [1,3,-1,-3,5,3,6,7], k = 3` => `[3,3,5,5,6,7]`
2. `nums = [1], k = 1` => `[1]`
3. `nums = [4,2,2,1,3], k = 2` => máximos `[4,2,2,3]` y mínimos `[2,2,1,1]`.

## Contenido adicional
- `demos/demo_sliding_window_maximum.cpp`: ejemplo ejecutable con entrada de muestra.
- `benchmark/benchmark_sliding_window_maximum.cpp`: prueba de rendimiento para la solución.
- `docs/design.md`: diseño de la solución y complejidad.
- `docs/usage.md`: instrucciones de compilación y ejecución.
- `resultados/example_output.txt`: salida de ejemplo.
- `resultados/benchmark_results.txt`: resultados de benchmark de muestra.