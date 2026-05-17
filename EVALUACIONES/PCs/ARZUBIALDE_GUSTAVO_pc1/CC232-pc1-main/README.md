# Reporte de Solución

## Integrantes
- Gustavo Anthony Arzubialde Fierro - 20230205H
- Victor Hugo Cadillo Gutierrez - 20255514D

## Problema asignado
Problema 6 Counting Bits: Contar el número de bits en 1 en la representación binaria de un número entero.

## Enlace al enunciado de LeetCode
[[LeetCode - Number of 1 Bits]](https://leetcode.com/problems/counting-bits/description/)

## Especificación breve del problema
Dado un número entero `n`, devolver un **arreglo** donde cada posición `i` (0 ≤ i ≤ n) contenga la cantidad de bits en 1 de la representación binaria de `i`.  
En otras palabras, se debe calcular el número de bits en 1 para todos los enteros desde 0 hasta `n` inclusive y mostrar el resultado en forma de array.

## Entrada y salida
- **Entrada:** un entero `n`.
- **Salida:** un **arreglo** de tamaño `n + 1` donde cada posición `i` contiene el número de bits en 1 de la representación binaria de `i`, para todo `i` en el rango [0, n].

## Tamaño de entrada
- **Tamaño**: número de bits de `n` → `w = ⌊log₂(n)⌋ + 1`

## Descripción de la solución
Se implementaron dos métodos:
1. **`countOnes1` (Kernighan):** elimina un bit en 1 en cada iteración (`n &= (n-1)`).
2. **computeOptimized (programación dinámica)**: construye un arreglo de resultados reutilizando cálculos previos mediante la relación

`bits(i) = bits(i >> 1) + (i & 1)`

2. lo que permite calcular el número de bits en 1 de cada entero hasta n en tiempo lineal.

Además, se implementaron funciones para construir arreglos con los resultados (**compute** y **computeOptimized**), y una función auxiliar para imprimirlos.

## Justificación de determinismo y factibilidad
- **Determinismo:** el algoritmo siempre produce el mismo resultado para la misma entrada.
- **Factibilidad:** el problema es computable en tiempo finito y con recursos razonables.

## Argumento de finitud
- En `countOnes1`, cada iteración reduce el número de bits en 1, garantizando que el bucle termina.
- En `compute`, el bucle principal recorre de 0 hasta `n`, con un número finito de iteraciones (exactamente `n+1`), asegurando la terminación.
- En `computeOptimized`, el bucle recorre de 1 hasta `n`, también con un número finito de iteraciones, garantizando la terminación.

## Argumento de correctitud
- `countOnes1`: al terminar, `ones` contiene exactamente el número de bits eliminados.
- `compute`: cada posición del arreglo se calcula aplicando la función `func(i, counter)`, lo que asegura que el resultado refleje correctamente el número de bits en 1 de cada entero.
- `computeOptimized`: cada valor `result[i]` se obtiene como `result[i >> 1] + (i & 1)`, garantizando que se acumule correctamente el conteo de bits a partir de subproblemas más pequeños.

## Invariante
- En `countOnes1`: **invariante de bucle** → `ones` refleja el número de bits eliminados hasta el momento.
- En `compute`: **invariante de bucle** → para cada `i`, `result[i]` contiene el número correcto de bits en 1 calculado por la función pasada como parámetro.
- En `computeOptimized`: **invariante de bucle** → para cada `i`, `result[i]` contiene el número correcto de bits en 1 de la representación binaria de `i`.

## Monotonicidad
- En `countOnes1`: el número de bits en 1 de `n` decrece estrictamente en cada iteración.
- En `compute`: el arreglo `result` se construye de manera progresiva, acumulando resultados de cada llamada a la función.
- En `computeOptimized`: el arreglo `result` se construye de manera ordenada, reutilizando resultados previos para calcular los siguientes.

## Complejidad temporal
- `countOnes1`: O(log n) (≈ O(1) en enteros fijos).
- `compute`: O(n · T(func)) donde T(func) es el costo de la función de conteo usada.
- `computeOptimized`: O(n).

## Complejidad espacial
- `countOnes1`: O(1).
- `compute`: O(n).
- `computeOptimized`: O(n).

## Mejor, peor y promedio
- `countOnes1`: mejor caso O(1), peor caso O(log n), promedio O(log n).
- `compute`: siempre O(n · T(func)).
- `computeOptimized`: siempre O(n).

## Ubicación en la jerarquía de crecimiento
- `countOnes1`: O(log n).
- `compute`: O(n · T(func)).
- `computeOptimized`: O(n).

## Alternativa ingenua
Recorrer bit por bit con desplazamientos y máscaras, contando los unos. Complejidad O(log n), menos eficiente que la reducción paralela.

## Robustez, degeneración y reutilización
- **Robustez:** maneja correctamente casos extremos como `n = 0` y números con todos los bits en 1.
- **Degeneración:** `countOnesArray1` puede volverse costoso para valores grandes de `n`.
- **Reutilización:** funciones encapsuladas (`countOnesX`, `printArray`) favorecen modularidad y reutilización.

## INSTRUCCIONES PARA COMPILAR

Debido a los requerimientos de la práctica se realiza la compilación de dos formas.
1. Se compila con el cmake cuando se trabaja sobre el código por la facilidad que otorga el cmake y también para evaluar los sanitizers.
2. Se compila con un archivo bash para obtener los ejecutables con determinadas banderas.

Para compilar con el cmake se realiza lo siguiente:
1. Moverse a la carpeta build:
```bash
cd build
```
2. En la carpeta build ejecutar el cmake

```bash
cmake ..
cmake --build .
```

Para compilar con las banderas como la de depuración, etc, hacer en la carpeta principal del proyecto.
```bash
./compilacion.sh
```
### Si presenta errores de falta de permiso, primero tendrá que ejecutar, el siguiente comando para darle el permiso de ejecutable:
```bash
chmod +x compilacion.sh
```

## INSTRUCCIONES PARA COMPILAR

Los archivos obtenidos por el cmake se pueden ejecutar en la carpeta build de la siguiente manera:

```bash
./demo_countones
./benchmark
```

Los archivos obtenidos por el bash se pueden ejecutar en la carpeta build_with_flags de la siguiente manera:
```bash
./coverage
./profiling
./test_compacto
./test_depuracion
./test_optimizacion
./test_release
./test_O1
./test_O3
```

## INSTRUCCIONES PARA EJECUTAR PRUEBAS

En la carpeta build ejecutar:

```bash
ctest
```

O también puede ejecutar las pruebas de forma individual usando el ejecutable:
```bash
./test_internal
./test_extra
./edge_cases
```

## TABLA RESUMIDA DE BUILDS Y RESULTADOS

Tabla con resultados obtenidos de ejecutar el comando time en bash y du.

| Build                        | Tiempo de ejecución (s) | Tamaño ejecutable (KB) | Ruta del ejecutable                          |
|------------------------------|-------------------------|------------------------|----------------------------------------------|
| Depuración                   | 1.540                   | 128K                   | ./build_with_flags/test_depuracion           |
| Depuración optimizado        | 0.503                   | 124K                   | ./build_with_flags/test_optimizado           |
| Release                      | 0.401                   | 128K                   | ./build_with_flags/test_release              |
| Compacto                     | 0.454                   | 120K                   | ./build_with_flags/test_compacto             |
| -O1                          | 0.488                   | 128K                   | ./build_with_flags/test_O1                   |
| -O3 compacto                 | 0.498                   | 136K                   | ./build_with_flags/test_O3                   |

Al ser ejecutables de test y al no activar los asserts, las pruebas se ejecutaron correctamente, siguiendo los comportamientos esperables.

## OBSERVACION DE LOS SANITIZERS

Hubo una advertencia sobre tipos incompatibles entre int y static, que se corrigió y
no debería haber otro problema ya que no se usan punteros de forma directa en el código, 
solo en las librerías internas de c++.

## DESCRIPCION DEL BENCHMARK

Se realizo un benchmark para comparar el STL, la versión ingenua y la optimizada.
La version STL usa instrucciones de CPU por lo que es más rápido aunque realice más bucles que
la versión optimizada, la versión ingenua recorre uno por uno las opciones hasta hacer todos los bits cero y
la versión optimizada usa calculos anteriormente obtenidos.

Resultados del benchmark

=== Benchmark (n = 10000000) ===

| Metodo       | Tiempo (ms) | Operaciones  |
|-------------|------------|-------------|
| STL         | 129        | 124434633   |
| countOnes1  | 817        | 124434633   |
| Optimizado  | 299        | 10000000    |

## RESUMEN DE COBERTURA

Para el profiling viendo:

```bash
gcov ./build_with_flags/coverage-count_ones_array.gcno
```
Da que solo se ejecutaron del total:
Lines executed:58.50% of 306

```bash
gcov ./build_with_flags/coverage-count_ones.gcda
```
Lines executed:100.00% of 7

```bash
gcov ./build_with_flags/coverage-loop_counter.gcda
```
Lines executed:100.00% of 9

```bash
gcov ./build_with_flags/coverage-test_internal.gcda
```
Lines executed:74.29% of 175

Se puede observar que solo de las funciones o clase base se ejecutaron todas sus líneas,
mientras que las otras solo parcialmente.

## RESUMEN DE PROFILING

## Resultados de Profiling

| % Tiempo | Tiempo total | Tiempo propio | Llamadas     | Promedio propio | Promedio total | Función                                                                 |
|----------|--------------|---------------|--------------|-----------------|----------------|-------------------------------------------------------------------------|
| 50.00    | 0.06         | 0.06          | 183321836    | 0.00            | 0.00           | LoopCounter::increment(unsigned long long)                              |
| 25.00    | 0.09         | 0.03          | 15016476     | 0.00            | 0.01           | countOnes1(unsigned int, LoopCounter&)                                  |
| 16.67    | 0.11         | 0.02          | —            | —               | —              | _init                                                                   |
| 8.33     | 0.12         | 0.01          | 102          | 98.04           | 932.21         | CountOnesArray::compute(unsigned int, int (*)(unsigned int, LoopCounter&), LoopCounter&) |
| 0.00     | 0.12         | 0.00          | 204          | 0.00            | 0.00           | LoopCounter::reset()                                                    |
| 0.00     | 0.12         | 0.00          | 102          | 0.00            | 48.18          | CountOnesArray::computeOptimized(unsigned int, LoopCounter&)            |
| 0.00     | 0.12         | 0.00          | 102          | 0.00            | 0.00           | LoopCounter::get() const                                                |
| 0.00     | 0.12         | 0.00          | 102          | 0.00            | 0.00           | std::vector<int, std::allocator<int> >::reserve(unsigned long)          |
| 0.00     | 0.12         | 0.00          | 100          | 0.00            | 0.00           | std::mersenne_twister_engine<...>::operator()()                         |
| 0.00     | 0.12         | 0.00          | 4            | 0.00            | 0.00           | std::_Vector_base<int, std::allocator<int> >::~_Vector_base()           |
| 0.00     | 0.12         | 0.00          | 2            | 0.00            | 0.00           | LoopCounter::LoopCounter()                                              |
| 0.00     | 0.12         | 0.00          | 1            | 0.00            | 0.00           | std::mersenne_twister_engine<...>::_M_gen_rand()                        |

Como se puede observar lo que se ejecuta más es el observable que nos permite saber cuántas veces se ejecuta un bucle,
después es la función countOnes y en tercer lugar es la clase que crea el array de salida.


## DISCUSIÓN SOBRE MICROOPTIMIZACIÓN VS ALGORITMO

Como se puede observar en el reporte sobre los ejecutables, no hay mejoras considerables usando las 
flags -O1 u -O3, sin embargo la elección de un algoritmo diferente, que reutiliza los cálculos anteriores
si muestra una mejora considerable, del 250%.

## QUÉ SE USO DE COPILOT Y CÓMO SE VALIDÓ

El asistente IA se utilizó principalmente para obtener un boilerplate de códigos, así como para hacer 
debugging de algunos errores, se validó mediante la lectura del código y la ejecución de las pruebas.
