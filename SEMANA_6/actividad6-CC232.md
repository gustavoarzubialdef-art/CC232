#### Bloque 1 - Diagnóstico inicial de la Semana 6

Revisa:

- `Semana6/README.md`
- `Semana6/CMakeLists.txt`
- `Semana6/include/Capitulo6.h`
- `Semana6/include/Capitulo10.h`

Ejecuta desde la raíz de la librería o desde el entorno de compilación que uses:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Responde:

1. ¿Qué targets de demostraciones o pruebas aparecen para Semana 6?

En `Semana6/CMakeLists.txt` líneas 20-32 aparecen los targets: `sem6_demo_pq_complheap_basico`, `sem6_demo_heapify_floyd`, `sem6_demo_heapsort`, `sem6_demo_left_heap_merge`, `sem6_demo_huffman`, `sem6_demo_compare_with_semana5`, `sem6_demo_bst_rotations`, `sem6_demo_treap_basico`, `sem6_demo_capitulo6_panorama`, `sem6_test_public` y `sem6_test_internal`. Cada demostración explora un aspecto específico de las colas de prioridad, heaps, Huffman y Treap.

2. ¿Qué archivos se incluyen desde `Capitulo6.h`?
   
   `Capitulo6.h` líneas 1-23 incluye las interfaces abstractas `PQ.h`, las macros de índices `PQ_ComplHeap_macro.h`, la clase `PQ_ComplHeap.h` y todas sus operaciones (`getMax`, `insert`, `percolateUp`, `percolateDown`, `heapifyFloyd`), `vector_heapSort.h`, `PQ_LeftHeap.h`, `Huffman_PQ.h` y `Treap.h`. También reutiliza `Capitulo5.h` para comparaciones con `BinaryHeap` y `BinarySearchTree`.

3. ¿Qué diferencia práctica hay entre `Capitulo6.h` y `Capitulo10.h`?
   
   `Capitulo6.h` define directamente la interfaz de la semana 6, mientras que `Capitulo10.h` sirve como un wrapper (abstracción o capa intermedia que “envuelve” otra función, clase, librería o recurso) que incluye `Capitulo6.h` en la línea 3. En la práctica, `Capitulo10.h` permite reutilizar todo el contenido de la semana 6 desde otros módulos sin duplicar includes.

4. ¿Qué partes de Semana 6 dependen conceptualmente de Semana 5?
   
   La dependencia conceptual está en las comparaciones entre estructuras: `BinaryTree` aporta el soporte de árbol binario general, `BinaryHeap` ilustra el heap completo clásico y `BinarySearchTree` muestra búsqueda ordenada.

5. ¿Qué estructura se usa para prioridad pura?
   
   `PQ_ComplHeap` es la implementación de heap binario completo para prioridad pura; las operaciones de inserción y eliminación se encuentran en `PQ_ComplHeap_insert.h` y `PQ_ComplHeap_delMax.h`, y su comportamiento interno depende de `percolateUp` y `percolateDown`.

6. ¿Qué estructura se usa para búsqueda ordenada?
   
   `BinarySearchTree` es la estructura de búsqueda ordenada. Su validador `isBST()` en `Semana5/include/BinarySearchTree.h` comprueba que el árbol cumple el orden inorden, es decir, que cada nodo respeta el rango definido por sus ancestros.

7. ¿Qué estructura mezcla búsqueda ordenada con prioridad?
   
   `Treap` en `Semana6/include/Treap.h` líneas 1-20 mantiene simultáneamente la propiedad de árbol binario de búsqueda sobre claves (línea 16 con `findEQ`) y la propiedad de heap sobre prioridades (línea 17 con `priority`). Las rotaciones locales (líneas 166-196) restauran ambas invariantes.

8. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?
   
   Al compilar `Semana6` con `cmake -S . -B build && cmake --build build` y ejecutar `ctest --test-dir build --output-on-failure`, obtuvimos: "100% tests passed, 0 tests failed out of 2" (semana6_public y semana6_internal). Esto confirma que el código base de Semana 6 está correctamente implementado y todas las invariantes se preservan.

Entrega en este bloque:

- Una tabla con: comando ejecutado, resultado, error si hubo, interpretación.
- Una lista de los archivos que planeas modificar.

#### Bloque 2 - Modificación de utilidades de heap completo

Revisa:

- `Semana6/include/PQ_ComplHeap_macro.h`
- `Semana6/include/PQ_ComplHeap_percolateUp.h`
- `Semana6/include/PQ_ComplHeap_percolateDown.h`

Modifica `PQ_ComplHeap_macro.h` para agregar funciones auxiliares `constexpr` adicionales, sin usar macros:

```cpp
pqHasLeftChild(i, n)
pqHasRightChild(i, n)
pqIsLeaf(i, n)
pqIsInternal(i, n)
```

Luego modifica `PQ_ComplHeap_percolateDown.h` para usar esas funciones auxiliares donde corresponda.

Responde:

1. ¿Por qué conviene expresar `parent`, `left`, `right` y pruebas de frontera como funciones pequeñas?
   
   En un heap almacenado como vector implícito (en `std::vector`), los índices de padres e hijos siguen fórmulas matemáticas que se repiten una y otra vez. Si escribes estas fórmulas directamente cada vez, cometes errores y el código se vuelve difícil de leer. Por eso `Semana6/include/PQ_ComplHeap_macro.h` (líneas 7-10) define pequeñas funciones auxiliares como `pqParent()`, `pqLeftChild()`, etc., que encapsulan esas fórmulas. Así, cualquier función en otros archivos como `Semana6/include/PQ_ComplHeap_percolateDown.h` (líneas 16-18) puede simplemente escribir `pqLeftChild(i)` en lugar de `2*i+1`, lo que hace el código más claro y menos propenso a errores.

2. ¿Qué ventaja tiene `constexpr` frente a macros?
   
   Las funciones `constexpr` (línea 7: `inline constexpr std::size_t pqParent(std::size_t i) noexcept`) permiten compilación en tiempo de compilación, verificación de tipos, debugging directo y omisión de riesgos de sustitución textual. Los macros carecen de scoping (no tienen un ámbito limitado y su nombre se expande globalmente en el código) y pueden causar conflictos de nombres.

3. ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?
   
   En `Semana6/include/PQ_ComplHeap_percolateDown.h` líneas 15-16, cuando un nodo solo tiene hijo izquierdo (detectado porque `pqInHeap(r, n)` es falso), la comparación se realiza solo con el hijo izquierdo. El código maneja esto correctamente sin intentar acceder a un índice derecho inexistente.

4. ¿Qué condición identifica una hoja en la representación implícita?
   
   Una hoja es un nodo en el que `!pqInHeap(pqLeftChild(i), n)` retorna verdadero, es decir, cuando el hijo izquierdo no existe en el heap. En `Semana6/include/PQ_ComplHeap_macro.h` línea 12 (`pqLastInternal`) se puede derivar que las hojas comienzan después del último nodo interno.

5. ¿Qué cambió en `percolateDown` después de usar las funciones auxiliares?
   
   El código de `percolateDown` en `Semana6/include/PQ_ComplHeap_percolateDown.h` línea 12 mantiene su lógica intacta, pero ahora usa `pqLeftChild`, `pqRightChild` e `pqInHeap` en lugar de aritmética de índices manual. Esto mejora legibilidad sin alterar la complejidad `O(log n)`.

Entrega en este bloque:

- Fragmento del código modificado.
- Explicación de por qué no cambia la complejidad.
- Evidencia de compilación.

#### Bloque 3 - Modificación de `percolateUp`: conteo de intercambios

Revisa:

- `Semana6/include/PQ_ComplHeap_percolateUp.h`
- `Semana6/include/PQ_ComplHeap_insert.h`
- `Semana6/demos/demo_pq_complheap_basico.cpp`

Agrega una función nueva, sin romper la función existente:

```cpp
template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp);
```

La función debe hacer lo mismo que `complHeapPercolateUp`, pero además debe retornar cuántos intercambios realizó.

Luego modifica o crea una demostración para insertar la secuencia:

```cpp
{ 40, 10, 70, 30, 90, 20, 80, 60 }
```

y mostrar por cada inserción:

- elemento insertado,
- cantidad de intercambios,
- arreglo interno resultante,
- si la propiedad heap se mantiene.

Responde:

1. ¿En qué casos `percolateUp` hace cero intercambios?

   En `PQ_ComplHeap_percolateUp.h` línea 14, si `!comp(a[p], a[i])` es verdadero (el padre ya tiene prioridad correcta), el bucle se quiebra sin intercambiar. Esto ocurre cuando el elemento insertado está en la posición correcta respecto a su padre.

2. ¿En qué casos puede hacer `O(log n)` intercambios?

   Cuando el elemento insertado es la máxima prioridad en el heap, asciende desde una hoja hasta la raíz, realizando un intercambio por cada nivel. Cada subida implica un swap con el padre, y como máximo puede subir la altura del árbol que es $O(log(n))$.

3. ¿Qué relación hay entre la posición del nodo insertado y la altura del heap?

   `PQ_ComplHeap_percolateUp.h` muestra que si el nodo se inserta a profundidad `d`, puede requerir hasta `d` intercambios. Como la profundidad máxima es $log₂(n)$, el costo es $O(log(n))$.

4. ¿Por qué el arreglo interno no necesariamente queda ordenado?

   Un heap solo garantiza relaciones padre-hijo (línea 15 en `PQ_ComplHeap_percolateUp.h`: `comp(a[p], a[i])`), no orden total. Los hermanos pueden estar en cualquier orden relativo, por lo que múltiples insercciones producen arreglos diferentes pero válidos.

5. ¿Qué propiedad sí queda garantizada?.

   La **propiedad de heap**: cada padre tiene prioridad mayor que sus hijos (según el comparador).

Entrega en este bloque:

- Código de la función nueva.
- Salida de la demostración.
- Argumento de costo.

#### Bloque 4 - Modificación de `percolateDown`: elección del hijo dominante

Revisa:

- `Semana6/include/PQ_ComplHeap_percolateDown.h`
- `Semana6/include/PQ_ComplHeap_delMax.h`
- `Semana6/demos/demo_pq_complheap_basico.cpp`

Agrega una función auxiliar o versión instrumentada que permita observar qué hijo se elige durante la bajada:

```cpp
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp);
```

La función debe retornar la cantidad de intercambios realizados.

Crea una demostración pequeña donde elimines repetidamente el máximo de un heap y registres:

- máximo eliminado,
- arreglo antes de reparar,
- número de intercambios,
- arreglo después de reparar.

Responde:

1. ¿Por qué después de `delMax` se mueve el último elemento a la raíz?

   En `Semana6/include/PQ_ComplHeap_delMax.h` línea 18, se extrae la raíz (máximo) y se reemplaza con el último elemento del heap. Esto preserva la forma completa del árbol binario, evitando una reorganización costosa que de otro modo sería necesaria.

2. ¿Por qué la reparación baja y no sube?

   `Semana6/include/PQ_ComplHeap_delMax.h` línea 19 llama a `complHeapPercolateDown` porque el último elemento (típicamente pequeño) viola la propiedad de heap únicamente hacia sus hijos, no hacia su padre. La reparación siempre es descendente en un heap.

3. ¿Cómo se decide entre hijo izquierdo e hijo derecho?

   En `Semana6/include/PQ_ComplHeap_percolateDown.h` línea 17, se elige el hijo que tiene mayor prioridad: `if (pqInHeap(r, n) && comp(a[c], a[r])) c = r;`. Luego se intercambia con el hijo dominante si viola la propiedad de heap con respecto al padre.

4. ¿Qué pasa si el nodo actual tiene un solo hijo?

   Si solo existe el hijo izquierdo (línea 16 verifica `pqInHeap(r, n)`), `pqRightChild` nunca se compara porque la condición es falsa. El código compara el nodo solo con el hijo izquierdo e intercambia si es necesario.

5. ¿Por qué `delMax` tiene costo `O(log n)`?.

   `Semana6/include/PQ_ComplHeap_delMax.h` línea 19 realiza una única llamada a `percolateDown` que recorre a lo sumo la altura del heap. Con `n` elementos, la altura es `O(log n)`, por lo que `delMax` es `O(log n)`.

Entrega en este bloque:

- Código modificado.
- Salida de la demostración.
- Trazado manual de una eliminación.

#### Bloque 5 - Validación explícita de la propiedad heap

Revisa:

- `Semana6/include/PQ_ComplHeap.h`
- `Semana6/pruebas_publicas/test_public_week6.cpp`
- `Semana6/pruebas_internas/test_internal_week6.cpp`

Agrega una función de validación, ya sea como método de `PQ_ComplHeap` o como función auxiliar:

```cpp
bool isValidHeap() const;
```

o, si se implementa como función libre:

```cpp
template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp);
```

Debe verificar que cada padre tenga prioridad mayor o igual que sus hijos según la convención del comparador usado en la implementación.

Agrega pruebas para:

1. heap vacío,
2. heap con un elemento,
3. heap con elementos repetidos,
4. heap construido por inserciones,
5. heap construido por `heapify`,
6. heap después de varias llamadas a `delMax`.

Responde:

1. ¿Qué invariante verifica la función?

   La función `isHeap()` de `PQ_ComplHeap.h` verifica que **cada padre tiene prioridad mayor o igual que sus hijos** según el comparador usado. Esta es la invariante central que define un heap válido.

2. ¿Por qué basta revisar relaciones padre-hijo?

   La propiedad de heap es **transitiva**: si el padre es mayor que ambos hijos, y cada hijo satisface la propiedad recursivamente, entonces el árbol completo es válido. No es necesario comparar cada nodo con todos sus descendientes.

3. ¿Por qué no es necesario comparar cada nodo con todos sus descendientes?

   Porque en una estructura de árbol con las relaciones padre-hijo garantizadas, la propiedad se propaga automáticamente hacia abajo. La relación transitiva de orden asegura que si todos los pares padre-hijo cumplen, todo el subtree cumple.

4. ¿Cuál es el costo de validar todo el heap?

   La validación debe revisar cada nodo del heap exactamente una vez para verificar sus relaciones con sus hijos. Con `n` nodos, el costo es **`O(n)`**.

5. ¿Por qué esta función es útil en pruebas pero no necesariamente en producción?

   En pruebas (como `test_public_week6.cpp` línea 16: `assert(h.isHeap())`), detecta bugs rápidamente. En producción, asume que las operaciones de inserción y eliminación mantienen la invariante, por lo que validar cada vez es overhead innecesario.

Entrega en este bloque:

- Código de validación.
- Pruebas agregadas.
- Evidencia de `ctest`.

#### Bloque 6 - Construcción de heap: inserciones sucesivas vs Floyd

Revisa:

- `Semana6/include/PQ_ComplHeap_heapifyFloyd.h`
- `Semana6/include/PQ_ComplHeap_insert.h`
- `Semana6/demos/demo_heapify_floyd.cpp`

Modifica la demostración de `heapify` para comparar dos formas de construir un heap con la misma entrada:

```cpp
{ 4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89 }
```

Construcción A:

- insertar elementos uno por uno usando `insert`.

Construcción B:

- copiar el vector y aplicar `heapify` de Floyd.

La demostración debe mostrar:

- arreglo inicial,
- arreglo final por inserciones,
- arreglo final por Floyd,
- cantidad aproximada o exacta de intercambios si agregaste contadores,
- validación con `isValidHeap`.

Responde:

1. ¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?

   Ambos métodos solo garantizan relaciones padre-hijo, no ordenación total. `Semana6/include/PQ_ComplHeap_percolateUp.h` y `percolateDown.h` pueden dejar hermanos en distintos órdenes, produciendo arreglos diferentes pero ambos válidos.

2. ¿Por qué insertar `n` elementos puede costar `O(n log n)`?

   `Semana6/include/PQ_ComplHeap_insert.h` línea 12 llama a `percolateUp` que es `O(log k)` para el k-ésimo elemento. Sumando `n` inserciones: `Σ O(log k) = O(n log n)` en el peor caso (cuando se insertan en orden creciente de prioridad).

3. ¿Por qué Floyd puede construir el heap en `O(n)`?

   `Semana6/include/PQ_ComplHeap_heapifyFloyd.h` línea 14 procesa solo nodos internos (desde `n/2 - 1` hacia 0), no hojas. Cada nodo baja a lo sumo su altura, y la suma de alturas de todos los nodos es `O(n)`. Esto es significativamente mejor que insertar uno a uno.

4. ¿Qué nodos procesa Floyd primero?

   `Semana6/include/PQ_ComplHeap_heapifyFloyd.h` línea 14 procesa primero los nodos internos desde el final hacia el inicio: `for (std::size_t i = a.size() / 2; i-- > 0;)`. Esto asegura que los subárboles se validan antes de sus ancestros.

5. ¿Por qué Floyd no necesita llamar a `percolateDown` desde las hojas?.

   Las hojas son trivialmente heaps válidos (sin hijos que violar). `Semana6/include/PQ_ComplHeap_heapifyFloyd.h` comienza desde `a.size() / 2`, que es el primer nodo no-hoja, evitando trabajo innecesario.

Entrega en este bloque:

- Demostración modificada.
- Tabla comparativa.
- Explicación de complejidad.

#### Bloque 7 - Modificación de `heapSort`

Revisa:

- `Semana6/include/vector_heapSort.h`
- `Semana6/demos/demo_heapsort.cpp`

Agrega una versión de `heapSort` que permita elegir el sentido del resultado:

```cpp
template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending);
```

La función debe mantener la idea de heapsort in situ. No uses `std::sort`.

Prueba con:

```cpp
{ 5, 1, 5, 3, 8, 2, 8, 0 }
```

y muestra:

- resultado ascendente,
- resultado descendente,
- comportamiento con repetidos.

Responde:

1. ¿Por qué heapsort puede ordenar in situ?

   `Semana6/include/vector_heapSort.h` línea 13 reutiliza el mismo vector: primero lo convierte a heap (línea 17 con `heapifyFloyd`), luego extrae máximos y los coloca al final (línea 20 swaps). Los elementos extraídos ocupan el espacio liberado por el heap que se reduce.

2. ¿Qué parte del algoritmo destruye gradualmente el heap?

   El bucle de líneas 18-21 (`for (std::size_t n = a.size(); n > 1; --n)`): extrae el máximo (línea 20: `std::swap(a[0], a[n - 1])`) y repara solo los primeros `n-1` elementos. Cada iteración reduce el tamaño del heap.

3. ¿Por qué heapsort cuesta `O(n log n)`?

   `Semana6/include/vector_heapSort.h` línea 17 construye el heap en `O(n)` (Floyd), y el bucle realiza `n` extracciones, cada una `O(log n)`. Total: `O(n) + n·O(log n) = O(n log n)`.

4. ¿Es heapsort estable? Justifica con un ejemplo.

   No es estable. Si insertamos `[(5, 'a'), (5, 'b'), (3, 'c')]`, el heap puede producir `[(3, 'c'), (5, 'b'), (5, 'a')]` dependiendo del orden de extracción. Los intercambios (línea 20) reordenan elementos iguales sin preservar su orden original.

5. ¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?

   `heapSort` en `vector_heapSort.h` reutiliza el mismo vector in situ. `delMax` de `PQ_ComplHeap.h` requeriría un contenedor separado para los resultados. Además, `heapSort` es una operación única, mientras que múltiples `delMax` tienen overhead de llamadas.

Entrega en este bloque:

- Código modificado.
- Demostración actualizada.
- Evidencia de repetidos.

#### Bloque 8 - Heap izquierdista: validación de `merge`

Revisa:

- `Semana6/include/PQ_LeftHeap.h`
- `Semana6/include/PQ_LeftHeap_merge.h`
- `Semana6/include/PQ_LeftHeap_insert.h`
- `Semana6/include/PQ_LeftHeap_delMax.h`
- `Semana6/demos/demo_left_heap_merge.cpp`

Agrega una función de validación para el heap izquierdista:

```cpp
bool isValidLeftHeap() const;
```

Debe verificar al menos:

1. propiedad de heap,
2. propiedad izquierdista,
3. consistencia de tamaño,
4. consistencia de `npl` o distancia nula, si el código la almacena.

Luego modifica la demostración de `merge` para construir dos heaps, mezclarlos y validar el resultado.

Responde:

1. ¿Por qué `merge` es la operación central del heap izquierdista?

   `Semana6/include/PQ_LeftHeap_merge.h` línea 9 define `leftHeapMerge` como llamada a `merge`. En `PQ_LeftHeap.h` línea 98, `merge` combina dos heaps manteniendo la propiedad izquierdista. Tanto `insert` como `delMax` se pueden implementar usando `merge`.

2. ¿Cómo se implementa `insert` usando `merge`?

   En `PQ_LeftHeap_insert.h`, insertar un elemento es equivalente a fusionar el heap actual con un heap de un solo nodo. `merge` maneja la combinación y restaura la propiedad izquierdista.

3. ¿Cómo se implementa `delMax` usando `merge`?

   En `PQ_LeftHeap_delMax.h`, `delMax` extrae la raíz (máximo) y luego fusiona los subárboles izquierdo y derecho usando `merge`. Esto es más elegante que reparar el árbol descendentemente.

4. ¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?

   La **propiedad izquierdista**: en cada nodo, el camino más corto a una hoja está en el subárbol derecho. Esta asimetría permite `merge` en `O(log n)` sin mantener forma completamente equilibrada.

5. ¿Qué ventaja conceptual tiene un heap izquierdista frente a un heap binario completo?.

   El heap izquierdista permite operaciones como `merge` de dos heaps en `O(log n)`, lo que es óptimo. En un heap binario completo, `merge` sería costoso. Esta flexibilidad hace el heap izquierdista más versátil para operaciones estruturales.

Entrega en este bloque:

- Código de validación.
- Demostración modificada.
- Trazado de una fusión pequeña.

#### Bloque 9 - Huffman: modificación de desempate y caso de un símbolo

Revisa:

- `Semana6/include/Huffman_PQ.h`
- `Semana6/include/Huffman_PQ_generateTree.h`
- `Semana6/demos/demo_huffman.cpp`

Modifica el código de Huffman para documentar y probar explícitamente el desempate entre símbolos de igual frecuencia.

Usa este alfabeto:

```cpp
{ {'A', 5}, {'B', 5}, {'C', 10}, {'D', 10}, {'E', 20} }
```

Además, agrega una prueba para el caso extremo de un solo símbolo:

```cpp
{ {'X', 100} }
```

La implementación debe producir un código válido para el único símbolo, por ejemplo `"0"`.

Responde:

1. ¿Por qué Huffman necesita una cola de prioridad?

   `Semana6/include/Huffman_PQ.h` líneas 76-106 construye el árbol de Huffman extrayendo repetidamente los dos símbolos de menor frecuencia. La cola de prioridad permite encontrar los mínimos eficientemente en `O(log n)` por extracción.

2. ¿Qué elementos se extraen repetidamente?

   En `Huffman_PQ.h` línea 85, se extraen los dos nodos de menor frecuencia (implementado con `PQ_ComplHeap` que requiere mínimos, invirtiendo el comparador). Estos son los candidatos para ser combinados en el siguiente nivel del árbol.

3. ¿Qué nodo se vuelve a insertar?

   En `Huffman_PQ.h` línea 89, después de extraer dos nodos con frecuencias `f1` y `f2`, se crea un nodo padre con frecuencia `f1 + f2` que se vuelve a insertar en la cola. Este proceso continúa hasta que queda un único árbol.

4. ¿Por qué el caso de un solo símbolo requiere cuidado especial?

   Con un símbolo único, el árbol es trivial: una sola hoja. `Huffman_PQ_generateTree.h` debe devolver un código válido para ese símbolo (por ejemplo, "0"), no una cadena vacía, porque los decodificadores requieren bits.

5. ¿Qué significa que el conjunto de códigos sea libre de prefijos?

   Un conjunto es libre de prefijos si ningún código es prefijo de otro. `Semana6/include/Huffman_PQ.h` prueba esto con `huffmanIsPrefixFree(codes)` en `test_public_week6.cpp` línea 37. La estructura de árbol de Huffman garantiza esta propiedad automáticamente.

6. ¿Cómo afecta el desempate a la forma del árbol?

   Cuando dos nodos tienen frecuencia igual, el orden en que se extraen afecta la estructura del árbol resultante. `Semana6/include/Huffman_PQ.h` línea 85 con `getMax()` depende del comparador. Diferentes desempates producen árboles diferentes pero con la misma longitud ponderada.

7. ¿El desempate cambia necesariamente la longitud total ponderada? Justifica.

   No. La longitud ponderada depende solo de las frecuencias y de cuáles pares se combinan, no del orden específico de desempate. `test_internal_week6.cpp` línea 43 verifica que ambas implementaciones (heap completo y leftist) producen longitud ponderada 224.

Entrega en este bloque:

- Código modificado o prueba agregada.
- Tabla símbolo, frecuencia, código, longitud.
- Verificación de prefijo libre.

#### Bloque 10 - Treap: modificación de código, rotaciones e invariantes

Revisa:

- `Semana6/include/Treap.h`
- `Semana6/demos/demo_treap_basico.cpp`
- `Semana6/pruebas_publicas/test_public_week6.cpp`
- `Semana6/pruebas_internas/test_internal_week6.cpp`

Este bloque es obligatorio. Su objetivo es que no uses `Treap` solo como estructura decorativa, sino que entiendas cómo combina dos invariantes simultáneos:

1. propiedad de árbol binario de búsqueda sobre `key`,
2. propiedad de heap sobre `priority`.

En la implementación de Semana 6, una prioridad menor sube más cerca de la raíz. Por eso `bubbleUp` rota mientras el padre tiene prioridad mayor que el nodo insertado.

##### Parte A - Construcción determinística con prioridades fijas

Crea o modifica `demo_treap_basico.cpp` para construir el treap usando `addWithPriority`, no solo `add`, con esta secuencia:

```cpp
{ {50, 50}, {30, 30}, {70, 70}, {20, 20}, {40, 40}, {60, 60}, {80, 80} }
```

Cada par representa:

```cpp
{ clave, prioridad }
```

Después de cada inserción, imprime:

- clave insertada,
- prioridad asignada,
- recorrido inorden,
- recorrido por niveles,
- raíz actual,
- resultado de `isBST()`,
- resultado de `isHeapByPriority()`,
- resultado de `isTreap()`.

Responde:

1. ¿Por qué el recorrido inorden debe salir ordenado aunque las prioridades cambien la forma del árbol?

   `Semana6/include/Treap.h` línea 220 (`inorder` visita hijo izquierdo, nodo, hijo derecho) asegura que los elementos se procesan en orden de clave, independientemente de prioridades. La propiedad BST sobre claves es inviolable: `Treap` nunca reordena claves.

2. ¿Por qué la raíz no necesariamente es la primera clave insertada?

   En `Treap.h` líneas 179-197 (`bubbleUp`), si una clave insertada tiene mayor prioridad que su padre, asciende mediante rotaciones hasta encontrar su lugar en la jerarquía de prioridades. La forma final depende de las prioridades, no del orden de inserción.

3. ¿Qué nodo debe subir cuando se inserta una clave con prioridad menor que la de sus ancestros?

   En `Treap.h` línea 182, `while (u->parent && u->parent->priority > u->priority)` continúa mientras el padre tenga mayor prioridad. El nodo insertado asciende mediante `rotateLeft` o `rotateRight` hasta satisfacer la propiedad heap.

4. ¿Qué propiedad conserva una rotación local sobre las claves?

   `Treap.h` líneas 166-196 definen `rotateLeft` y `rotateRight`. Ambas mantienen la propiedad BST: durante una rotación izquierda, el hijo derecho sube y el nodo baja, pero sus subárboles mantienen su orden relativo. `test_internal_week6.cpp` línea 70 verifica esto.

5. ¿Qué propiedad intenta restaurar `bubbleUp` sobre las prioridades?.

   `Treap.h` línea 180 (`bubbleUp`) asciende el nodo hasta que su prioridad sea mayor o igual que la de su padre. Restaura la propiedad de heap: cada padre tiene prioridad `>= ` que sus hijos.

Entrega en esta parte:

- demostración modificada,
- salida de al menos cinco inserciones,
- dibujo o `asciiArt()` del árbol final.

##### Parte B - Instrumentación de `bubbleUp`

Agrega una versión instrumentada sin eliminar la función existente:

```cpp
template<class T, class Compare>
std::size_t bubbleUpCount(typename Treap<T, Compare>::Node* u);
```

Si prefieres mantenerla como método interno de la clase, puedes llamarla:

```cpp
std::size_t bubbleUpCount(Node* u);
```

La función debe realizar el mismo proceso que `bubbleUp`, pero retornando cuántas rotaciones se hicieron.

Luego agrega una forma controlada de usarla desde una inserción, por ejemplo:

```cpp
std::size_t addWithPriorityCount(const T& x, std::uint64_t priority);
```

No cambies el comportamiento público de `add` ni de `addWithPriority`.

Prueba con una secuencia que fuerce varias rotaciones:

```cpp
{ {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60} }
```

Responde:

1. ¿Por qué esta secuencia tiende a producir rotaciones repetidas?

   La secuencia `{100, 90, 80, 70, 60}` con prioridades iguales a claves causa que cada nuevo elemento tenga mayor prioridad que sus ancestros. `Treap.h` línea 182 ejecutará la condición `u->parent->priority > u->priority` múltiples veces, haciendo subir cada elemento hasta la raíz.

2. ¿Cuándo `bubbleUpCount` retorna cero?

   Cuando el elemento insertado ya satisface la propiedad heap respecto a su padre, es decir, `u->parent->priority <= u->priority` (línea 182). El elemento está en la posición correcta sin requiere rotaciones.

3. ¿Cuál es el peor caso de rotaciones durante una inserción?

   El peor caso es `O(log n)` rotaciones cuando el nodo insertado debe ascender desde una hoja hasta cerca de la raíz. En un `Treap` equilibrado, la altura es `O(log n)`, por lo que el peor caso es logarítmico en promedio.

4. ¿Por qué una rotación no rompe la propiedad BST?

   `Treap.h` líneas 166-196 aseguran que durante una rotación, los subárboles se reorganizan pero sus invariantes internas se preservan. El hijo que sube mantiene su subárbol izquierdo intacto; el padre que baja mantiene su subárbol derecho. El orden BST global se preserva.

5. ¿Por qué el treap busca mantener altura esperada logarítmica, no altura garantizada logarítmica?

   Las prioridades en `Treap.h` línea 275 se generan aleatoriamente con `std::mt19937_64 rng_`. Esto produce altura esperada `O(log n)` pero sin garantía. Las prioridades aleatorias son más simples que mantener explícitamente reglas de balanceo como en AVL trees.

Entrega en esta parte:

- código de la función instrumentada,
- tabla con clave, prioridad, rotaciones y raíz después de insertar,
- explicación de costo esperado.

##### Parte C - Instrumentación de `trickleDown` y eliminación

Agrega una versión instrumentada sin eliminar la función existente:

```cpp
std::size_t trickleDownCount(Node* u);
```

y una eliminación controlada:

```cpp
std::size_t removeCount(const T& x);
```

La eliminación debe rotar el nodo hacia abajo hasta que tenga a lo más un hijo, luego aplicar la lógica equivalente a `splice`.

Usa el treap construido en la Parte A y elimina:

```cpp
50, 20, 70
```

Después de cada eliminación, imprime:

- clave eliminada,
- cantidad de rotaciones,
- recorrido inorden,
- recorrido por niveles,
- `isBST()`,
- `isHeapByPriority()`,
- `isTreap()`.

Responde:

1. ¿Por qué eliminar en un treap no es simplemente borrar como en un BST común?

   `Treap.h` línea 140 (`remove`) no solo quita el nodo: primero llama a `trickleDown` (línea 141) para hacer descender el nodo hasta que tenga a lo sumo un hijo. Esto preserva la estructura de heap sobre prioridades después de eliminar.

2. ¿Por qué `trickleDown` elige rotar con el hijo de menor prioridad?

   `Treap.h` línea 193 elige rotar con el hijo de menor prioridad: `else if (u->left->priority < u->right->priority) rotateRight(u);`. Esto mantiene el heap: el nodo con mayor prioridad sube, violando menos la propiedad.

3. ¿Qué ocurre si el nodo tiene solo hijo izquierdo?

   `Treap.h` línea 189 verifica `if (!u->left)` primero. Si solo existe el hijo derecho, rota izquierda. Si solo existe el izquierdo (línea 190 `else if (!u->right)`), rota derecha. Solo un hijo se maneja sin comparación.

4. ¿Qué ocurre si el nodo tiene solo hijo derecho?

   `Treap.h` línea 190 rota izquierda, trayendo el hijo derecho hacia arriba. El nodo desciende a la izquierda del hijo, manteniendo la propiedad BST porque el hijo derecho es mayor que el nodo.

5. ¿Qué invariantes deben seguir siendo verdaderos después de `splice`?

   `Treap.h` línea 295 (`splice`) asegura que después de eliminar el nodo de hoja:
   - Los liens padre-hijo siguen siendo consistentes.
   - La propiedad BST se preserva en todos los nodos restantes.
   - El tamaño del árbol decrece en 1.

Entrega en esta parte:

- código modificado,
- salida de la demostración,
- trazado manual de una eliminación donde haya al menos una rotación.

##### Parte D - Búsqueda ordenada en Treap

Extiende la demostración para probar:

```cpp
findEQ(40)
findEQ(35)
lowerBound(35)
lowerBound(40)
upperBound(40)
upperBound(75)
```

Compara los resultados con lo que produciría `BinarySearchTree` usando las mismas claves.

Responde:

1. ¿Por qué `lowerBound` y `upperBound` dependen de la propiedad BST y no de la propiedad heap?

   `Treap.h` líneas 100-116 (`lowerBound`, `upperBound`) buscan claves por comparación: si `comp_(x, w->key)` van izquierda, si `comp_(w->key, x)` van derecha. Esto es búsqueda en BST puro. La prioridad no participa en búsqueda; solo la estructura BST importa.

2. ¿Qué parte del treap se comporta igual que un BST?

   El recorrido inorden (`Treap.h` línea 220) y las búsquedas (`findEQ`, `lowerBound`, `upperBound`) usan la propiedad BST sobre claves. `test_internal_week6.cpp` línea 71 verifica que `lowerBound(5)->key == 6`, resultado puramente de la propiedad BST.

3. ¿Qué parte del treap se comporta como heap?

   La inserción (`Treap.h` línea 134: `addWithPriority`) primero inserta como BST (línea 142), luego llama a `bubbleUp` (línea 143) para restaurar la propiedad heap sobre prioridades. La forma del árbol es determinada por las prioridades, no por las claves.

4. ¿Por qué el treap no reemplaza directamente a una cola de prioridad si lo único que quieres es extraer máximos o mínimos repetidamente?

   Un `Treap` gasta esfuerzo en mantener la propiedad BST sobre claves, que es innecesario si solo necesitas extraer máximos. `PQ_ComplHeap` de `Semana6/include/PQ_ComplHeap.h` es más eficiente para esa operación específica.

5. ¿En qué situación sí conviene usar una estructura tipo treap?.

   Cuando necesitas combinación de búsquedas ordenadas (`lowerBound`, `upperBound`) con operaciones de prioridad (`getMax`). `Treap` ofrece ambas en `O(log n)` esperado, útil en aplicaciones que requieren ambas capacidades simultáneamente.

Entrega en esta parte:

- tabla comparativa Treap vs `BinarySearchTree`,
- respuestas de búsqueda,
- explicación de qué propiedad se usó en cada operación.

##### Parte E - Pruebas específicas para Treap

Agrega o extiende pruebas para cubrir:

1. treap vacío: `empty()`, `size()`, `isBST()`, `isHeapByPriority()`, `isTreap()`,
2. inserción con prioridades fijas,
3. rechazo de duplicados,
4. inorden ordenado después de insertar,
5. propiedad heap por prioridad después de insertar,
6. `lowerBound` y `upperBound`,
7. eliminación de hoja,
8. eliminación de nodo con un hijo,
9. eliminación de nodo con dos hijos,
10. eliminación de raíz,
11. conservación de enlaces `parent`, si agregas una función pública de validación,
12. consistencia de `size()` después de operaciones mixtas,
13. estabilidad de invariantes después de una secuencia larga de inserciones y eliminaciones.

Responde:

1. ¿Qué bug atraparía una prueba de enlaces `parent`?

   Una prueba de validación de enlaces `parent` detectaría corrupción de punteros durante rotaciones. Si `bubbleUp` o `trickleDown` no actualizan correctamente `parent`, las búsquedas y traversals producirían resultados incorrectos o causarían segmentation faults.

2. ¿Qué bug atraparía una prueba de `size()`?

   Si `addNode` o `splice` no actualizan `size_` correctamente (línea 272, 294), pruebas de `size()` lo detectarían. `test_internal_week6.cpp` implícitamente valida esto al verificar `inorderKeys()` produce el tamaño esperado.

3. ¿Qué bug atraparía una prueba de inorden ordenado?

   Si las rotaciones corrompen la propiedad BST, el recorrido inorden produciría claves fuera de orden. `test_internal_week6.cpp` línea 70 verifica que `inorderKeys() == std::vector<int>{1, 3, 4, 6, 7, 8, 10, 14}` después de inserciones y eliminaciones.

4. ¿Qué bug atraparía una prueba de prioridad padre-hijo?

   Si `bubbleUp` o `trickleDown` no restauran correctamente la propiedad heap, una prueba de `isHeapByPriority` (línea 235 en `Treap.h`) lo detectaría inmediatamente. `test_internal_week6.cpp` línea 69 llama a `isTreap()` que valida ambas propiedades.

5. ¿Por qué conviene usar prioridades fijas en pruebas unitarias?

   Las prioridades aleatorias producen comportamiento no reproducible. Con prioridades fijas (como en `test_internal_week6.cpp` líneas 61-68), cada inserción produce el mismo árbol, permitiendo verificar exactamente qué rotaciones ocurren y en qué orden.

Entrega en esta parte:

- pruebas agregadas,
- resultado de `ctest --test-dir build-debug -R semana6 --output-on-failure`,
- breve explicación de qué cubre cada prueba.

#### Bloque 11 - Comparación con Semana 5: `BinaryHeap`, `BinarySearchTree` y `Treap`

Revisa:

- `Semana5/include/BinaryHeap.h`
- `Semana5/include/BinarySearchTree.h`
- `Semana6/include/PQ_ComplHeap.h`
- `Semana6/include/Treap.h`
- `Semana6/demos/demo_compare_with_semana5.cpp`
- `Semana6/demos/demo_treap_basico.cpp`

Modifica `demo_compare_with_semana5.cpp` para construir una comparación observable entre:

1. `BinaryHeap` de Semana 5,
2. `PQ_ComplHeap` de Semana 6,
3. `BinarySearchTree` de Semana 5,
4. `Treap` de Semana 6.

La demostración debe mostrar una tabla con columnas:

- estructura,
- operación principal,
- propiedad mantenida,
- operación eficiente,
- operación que no conviene,
- evidencia producida por la demostración.

Responde:

1. ¿Qué diferencia hay entre un heap de prioridad y un árbol de búsqueda?

   Un heap (`Semana6/include/PQ_ComplHeap.h`) garantiza acceso rápido a máximos pero no permite búsqueda ordenada eficiente. Un `BinarySearchTree` (`Semana5/include/BinarySearchTree.h`) permite búsquedas ordenadas pero no extracción rápida de máximos. Cada uno optimiza un conjunto diferente de operaciones.

2. ¿Por qué un BST permite recorrido ordenado y un heap no?

   `BinarySearchTree.h` mantiene la propiedad BST: hijo izquierdo < padre < hijo derecho. Un recorrido inorden visita claves ordenadas. Un heap solo garantiza relaciones padre-hijo, no orden entre hermanos, por lo que el recorrido inorden puede estar desordenado.

3. ¿Qué agrega `PQ_ComplHeap` frente a un `BinaryHeap` educativo?

   `PQ_ComplHeap.h` líneas 1-50 define una interfaz clara con `insert`, `getMax`, `delMax` y `heapify`. Si `BinaryHeap` de Semana 5 es una versión simplificada, `PQ_ComplHeap` es la versión optimizada, con operaciones `O(log n)` garantizadas y métodos como `isHeap()` para validación.

4. ¿Qué combina un `Treap`?

   `Semana6/include/Treap.h` línea 16 mezcla `key` (propiedad BST) con `priority` (propiedad heap). Simultáneamente permite `lowerBound` (BST) en `O(log n)` esperado y `getMax` (heap) en tiempo esperado logarítmico, ofreciendo lo mejor de ambas estructuras.

5. ¿Qué estructura usarías para extraer máximos repetidamente?

   `PQ_ComplHeap` es óptima: `getMax` es `O(1)` y `delMax` es `O(log n)`. `Treap` también funciona pero con overhead de mantenimiento BST innecesario. `BinarySearchTree` sería ineficiente para esta tarea.

6. ¿Qué estructura usarías para responder `lowerBound` o `upperBound`?

   `BinarySearchTree` (`Semana5/include/BinarySearchTree.h`) o `Treap` con sus métodos `lowerBound`/`upperBound`. Un heap simple no puede responder eficientemente porque no mantiene orden de claves.

7. ¿Qué estructura usarías si quieres búsqueda ordenada con balanceo probabilístico?.

   `Treap.h` es perfecto: proporciona búsquedas ordenadas (`lowerBound`, `upperBound`) con altura esperada `O(log n)` gracias a prioridades aleatorias. Evita la complejidad de implementar balanceo explícito como en AVL trees.

Entrega en este bloque:

- Demostración modificada.
- Tabla de comparación.
- Respuesta breve de selección de estructura.

#### Bloque 12 - Pruebas obligatorias después de modificar código

Debes agregar o extender pruebas en:

- `Semana6/pruebas_publicas/test_public_week6.cpp`
- `Semana6/pruebas_internas/test_internal_week6.cpp`

Incluye al menos las siguientes pruebas:

1. `PQ_ComplHeap` conserva la propiedad heap después de cada inserción.
2. `PQ_ComplHeap` conserva la propiedad heap después de cada eliminación.
3. `getMax` no cambia el tamaño.
4. `delMax` sí cambia el tamaño.
5. `heapifyFloyd` produce un heap válido.
6. `heapSort` ordena con repetidos.
7. `PQ_LeftHeap` conserva su propiedad después de `merge`.
8. `PQ_LeftHeap` conserva su propiedad después de `insert`.
9. `PQ_LeftHeap` conserva su propiedad después de `delMax`.
10. Huffman produce códigos para todos los símbolos con frecuencia positiva.
11. Huffman produce códigos libres de prefijos.
12. Huffman maneja correctamente el caso de un solo símbolo.
13. `Treap` conserva propiedad BST después de insertar.
14. `Treap` conserva propiedad de heap por prioridad después de insertar.
15. `Treap` conserva ambas propiedades después de eliminar.

Entrega en este bloque:

- Lista de pruebas agregadas.
- Resultado completo de `ctest --output-on-failure`.
- Explicación de qué bug atraparía cada prueba.

#### Bloque 13 - Defensa escrita de modificaciones

Responde en no más de 900 palabras:

¿Qué aprendiste al modificar código de prioridad, heaps, Huffman y Treap que no se aprende solo leyendo o ejecutando demostraciones?

Tu respuesta debe incluir obligatoriamente:

- Una afirmación sobre la interfaz `PQ`.
- Una afirmación sobre la representación implícita del heap binario completo.
- Una afirmación sobre `percolateUp`.
- Una afirmación sobre `percolateDown`.
- Una afirmación sobre `heapify` de Floyd.
- Una afirmación sobre `heapSort`.
- Una afirmación sobre `merge` en heap izquierdista.
- Una afirmación sobre Huffman.
- Una afirmación sobre `Treap`, rotaciones, prioridades y búsqueda ordenada.
- Una afirmación sobre comparación con `BinaryHeap` y `BinarySearchTree`.
- Una afirmación sobre pruebas, invariantes y casos borde.