#### Bloque 1 - Núcleo conceptual de la semana

Revisa:

- `Semana5/README.md`
- `Semana5/lecturas/Notas.md`
- `Semana5/include/BinNode.h`
- `Semana5/include/BinTree.h`
- `Semana5/include/BinaryTree.h`
- `Semana5/include/BinarySearchTree.h`
- `Semana5/include/BinaryHeap.h`

Responde:

1. Explica con tus palabras qué diferencia hay entre un árbol binario enlazado y un árbol binario almacenado implícitamente en un arreglo.

   Un árbol binario enlazado usa nodos con punteros **left, right y parent**; su estructura depende de los enlaces. Un árbol binario implícito usa un arreglo donde la relación padre/hijo se calcula por índices, sin punteros explícitos.

   En las cabeceras [BinNode.h] en las lineas 11-26 se muestra la estructura de nodo y [BinaryHeap.h] en las lineas 16-23 la representación implícita en arreglo.

2. Explica qué información guarda un `BinNode`: dato, padre, hijo izquierdo, hijo derecho y altura.

   Un **BinNode** guarda: el dato contenido, el puntero al padre, el puntero al hijo izquierdo, el puntero al hijo derecho y la altura del subárbol cuya raíz es ese nodo.

   solución en el texto; código: [BinNode.h]`BinNode.h#L11-L26` (miembros `data,parent,left,right,height`).

3. Explica por qué el puntero `parent` permite implementar operaciones como `succ()`, `pred()` y actualización ascendente de alturas.

   El puntero **parent** permite subir desde un nodo hacia la raíz, por eso `succ()` y `pred()` pueden retroceder cuando no hay descendiente adecuado; también permite propagar la actualización de alturas hacia arriba luego de un cambio local.

   solución en el texto; código: [BinNode.h]`BinNode.h#L94-L109` (`succ`) y [BinNode.h]`BinNode.h#L124-L139` (`pred`).

4. Explica qué responsabilidad tiene `BinTree` frente a `BinNode`.

   **BinTree** administra la raíz y el tamaño del árbol, crea y borra subárboles, y mantiene invariantes globales mientras `BinNode` define la estructura local de cada nodo.

   solución en el texto; código: [BinTree.h]`BinTree.h#L1-L20` (declaración) y [BinTree.h]`BinTree.h#L66-L74` (`updateHeight`).

5. Explica qué agrega `BinaryTree` sobre la infraestructura base de `BinTree`.

   **BinaryTree** agrega recorridos, iteradores y operaciones de navegación ordenada sobre la infraestructura base; hace que un **BinTree** sea un contenedor que puede recorrerse en inorden y que conoce primero/último nodo.

   solución en el texto; código: [BinaryTree.h]`BinaryTree.h#L1-L40` (iteradores y `firstNode`/`lastNode`).

6. Explica qué propiedad adicional convierte un árbol binario en un `BinarySearchTree`.

   Un árbol binario es un **BinarySearchTree** si para cada nodo, todos los valores del subárbol izquierdo son menores y todos los valores del subárbol derecho son mayores o iguales, según la definición usada.

   solución en el texto; código: [BinarySearchTree.h]`BinarySearchTree.h#L1-L24` (`findLast`, `findEQ`, `lowerBound`) y [BinarySearchTree.h]`BinarySearchTree.h#L216-L226)` (`isBST` helper).

7. Explica qué propiedad adicional convierte un arreglo en un `BinaryHeap` mínimo.

   Un arreglo es un **BinaryHeap** mínimo si para cada índice i, el elemento en i es menor o igual que sus hijos **left(i)** y **right(i)**.

   solución en el texto; código: [BinaryHeap.h]`BinaryHeap.h#L30-L39` (`top`,`add`) y [BinaryHeap.h](Libreria_cc232/Semana5/include/BinaryHeap.h#L91-L93) (`heapify`).

8. Compara la propiedad de orden de un BST con la propiedad de prioridad de un heap.

   El BST garantiza orden relativo entre todos los nodos, mientras que el heap garantiza que el nodo raíz sea el mínimo; el heap no ordena toda la secuencia, solo mantiene prioridad de la raíz.

   solución en el texto; código: [BinarySearchTree.h]`BinarySearchTree.h#L1-L24` y [BinaryHeap.h]`BinaryHeap.h#L1-L20`.

9. Explica por qué un recorrido inorden de un BST produce una secuencia ordenada.

   En un BST inorden, se visita primero el subárbol izquierdo, luego el nodo y luego el subárbol derecho; por la propiedad BST, eso produce una secuencia ordenada de menor a mayor.

   solución en el texto; código: [BinNode.h]`BinNode.h#L183-L189` (`travInRecursive`) y [BinarySearchTree.h]`BinarySearchTree.h#L1-L24` (propiedad BST aplicada).

10. Explica por qué un heap no permite, por sí solo, recorrer los elementos en orden sin destruir o copiar la estructura.

    El heap solo garantiza la propiedad local de prioridad, no orden total; para obtener elementos en orden es necesario extraer el mínimo repetidamente o copiar los datos a otra estructura ordenada.

    solución en el texto; código: [BinaryHeap.h]`BinaryHeap.h#L60-L71` (`bubbleUp`,`trickleDown`) y [BinaryHeap.h]`BinaryHeap.h#L102-L109` (`isHeapArray`).

#### Bloque 2 - Navegación, altura, profundidad y tamaño

Revisa:

- `Semana5/include/BinNode.h`
- `Semana5/include/BinTree.h`
- `Semana5/include/BinaryTree.h`
- `Semana5/demos/demo_binary_tree.cpp`

Responde:

1. En `BinNode`, explica qué significan `hasLeft()`, `hasRight()`, `isRoot()`, `isLeaf()`, `isLeftChild()` e `isRightChild()`.

   `hasLeft()` indica si el nodo tiene hijo izquierdo; `hasRight()` si tiene hijo derecho; `isRoot()` si no tiene padre; `isLeaf()` si no tiene hijos; `isLeftChild()` si es el hijo izquierdo de su padre; `isRightChild()` si es el hijo derecho.

   (hasLeft...): solución en el texto; código: [BinNode.h]`BinNode.h#L33-L39`.

2. Explica el caso en que `succ()` baja al subárbol derecho y luego busca el nodo más a la izquierda.

   Si `succ()` baja al subárbol derecho, busca el `leftmost()` dentro de ese subárbol porque el sucesor inorden es el menor nodo mayor que el actual.

   (casos `succ()`): solución en el texto; código: [BinNode.h]`BinNode.h#L94-L116` (descenso derecho y búsqueda leftmost) y [BinNode.h]`BinNode.h#L103-L109` (subida por ancestros).

3. Explica el caso en que `succ()` sube por los ancestros hasta encontrar el primer giro hacia la izquierda.

   Si no hay subárbol derecho, `succ()` sube por `parent` hasta encontrar un ancestro donde el nodo actual esté en la rama izquierda; ese ancestro es el sucesor.

   (casos `succ()`): solución en el texto; código: [BinNode.h]`BinNode.h#L94-L116` (descenso derecho y búsqueda leftmost) y [BinNode.h]`BinNode.h#L103-L109` (subida por ancestros).

4. Explica simétricamente cómo debe funcionar `pred()`.

   `pred()` es simétrico: si tiene subárbol izquierdo, baja a `rightmost()` de ese subárbol; si no, sube por `parent` hasta encontrar un ancestro donde el nodo actual esté en la rama derecha.

   (`pred()`): solución en el texto; código: [BinNode.h]`BinNode.h#L124-L139`.

5. Dibuja un árbol de al menos 7 nodos y marca el sucesor y predecesor inorden de tres nodos distintos.

   ```
         8
       /   \
      4     12
     / \   /  \
    2   6 10  14
   ```

   - Sucesor de 6: 8. Predecesor de 6: 4.
   - Sucesor de 4: 6. Predecesor de 4: 2.
   - Sucesor de 10: 12. Predecesor de 10: 8.

   (dibujo ejemplo): solución en el texto; referencia funcional: [BinNode.h]`BinNode.h#L62-L86` (`leftmost`,`rightmost`).

6. Explica qué calcula `depth(u)` y por qué puede implementarse subiendo por `parent`.

   `depth(u)` cuenta el número de enlaces `parent` desde `u` hasta la raíz; puede calcularse subiendo por `parent` y sumando 1 por cada ancestro.

   (depth, height, subtreeSize): solución en el texto; código: [BinTree.h]`BinTree.h#L66-L74` (`updateHeight`) y [BinNode.h]`BinNode.h#L21-L29` (`size`).

7. Explica qué calcula `height(u)` y por qué suele implementarse bajando recursivamente por los hijos.

   `height(u)` mide la longitud del camino más largo desde `u` hasta una hoja; suele implementarse bajando recursivamente por `left` y `right` porque depende de los tamaños de los subárboles.

   (depth, height, subtreeSize): solución en el texto; código: [BinTree.h]`BinTree.h#L66-L74` (`updateHeight`) y [BinNode.h]`BinNode.h#L21-L29` (`size`).

8. Explica qué calcula `subtreeSize(u)`.

   `subtreeSize(u)` es el número de nodos en el subárbol cuya raíz es `u`; se calcula como 1 más el tamaño del subárbol izquierdo y el derecho.

   (depth, height, subtreeSize): solución en el texto; código: [BinTree.h]`BinTree.h#L66-L74` (`updateHeight`) y [BinNode.h]`BinNode.h#L21-L29` (`size`).

9. Demuestra que para todo nodo `u` se cumple `depth(u) + height(u) <= height(T)`.

   Para todo nodo `u`, cualquier camino desde la raíz hasta una hoja pasa por `u`, de modo que `depth(u) + height(u)` es la longitud de un camino desde la raíz hasta la hoja más profunda de ese subárbol, que no puede exceder `height(T)`.

   (relación depth+height): solución en el texto; código de ayuda: [BinTree.h]`BinTree.h#L66-L74` y definiciones de `height` en `BinNode.h`.

10. Indica la condición necesaria y suficiente para que se alcance la igualdad anterior.

    La igualdad se alcanza cuando `u` está en algún camino más largo desde la raíz a una hoja máxima, es decir, cuando `u` pertenece a un diámetro de árbol maximal.

    (relación depth+height): solución en el texto; código de ayuda: [BinTree.h]`BinTree.h#L66-L74` y definiciones de `height` en `BinNode.h`.

#### Bloque 3 - Recorridos y trazado guiado

Revisa:

- `Semana5/include/BinNode.h`
- `Semana5/include/BinTree.h`
- `Semana5/demos/demo_binary_tree.cpp`
- `Semana5/demos/demo_capitulo5_panorama.cpp`

Construye una tabla con cinco columnas:

- Recorrido
- Versión revisada
- Estructura auxiliar usada
- Secuencia producida en el árbol de prueba
- Argumento de correctitud y costo

Incluye en la tabla:

- preorden recursivo,
- preorden iterativo,
- inorden recursivo,
- inorden iterativo `#1`,
- inorden iterativo `#2`,
- inorden iterativo `#3`,
- postorden recursivo,
- postorden iterativo,
- recorrido por niveles.

Luego responde:

1. ¿Qué significa visitar un nodo en preorden?

   En preorden el nodo se procesa antes de sus hijos; el código recursivo está en `BinNode::travPre`, y la versión iterativa equivalente está en `BinNode::travPreIterative2`.

2. ¿Qué significa visitar un nodo en inorden?

   En inorden el nodo se procesa entre los hijos izquierdo y derecho; la versión recursiva se implementa en `BinNode::travInRecursive`.

3. ¿Qué significa visitar un nodo en postorden?

   En postorden los hijos se procesan antes que el nodo; la versión recursiva está en `BinNode::travPost`, mientras que la versión iterativa usa `BinNode::travPostIterative` con dos pilas.

4. ¿Qué significa visitar un árbol por niveles?

   El recorrido por niveles procesa nodos de menor a mayor profundidad; se implementa en `BinNode::travLevel` con una `std::queue`.

5. ¿Por qué los recorridos recursivos tienen tiempo `O(n)`?

   Los recorridos recursivos son `O(n)` porque cada nodo se visita una sola vez y cada llamada hace trabajo constante. `BinNode::travPre`, `BinNode::travInRecursive` y `BinNode::travPost` muestran este patrón.

6. ¿Por qué las versiones iterativas también tienen tiempo `O(n)`?

   Las versiones iterativas también son `O(n)` porque cada nodo entra y sale de la estructura auxiliar una vez. Las funciones `travPreIterative2`, `travInIterative1`, `travInIterative2`, `travInIterative3` y `travPostIterative` son ejemplos.

7. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol balanceado?

   En un árbol balanceado, la memoria auxiliar recursiva es `O(log n)` porque la pila de llamadas crece con la altura del árbol. En ese caso, `travInRecursive` o `travPost` solo usan una profundidad pequeña relativa a `n`.

8. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol degenerado?

   En un árbol degenerado, la misma pila de llamadas puede crecer hasta `O(n)`, ya que la profundidad puede ser igual al número de nodos.

9.  ¿Qué diferencia hay entre usar una pila explícita y usar la pila de llamadas?

    Una pila explícita se usa en `travInIterative1` y `travPostIterative`; la función recursiva equivalente `travInRecursive` o `travPost` usa la pila de llamadas en su lugar. El comportamiento es el mismo, pero el control es explícito en el código iterativo.

10. ¿Por qué la cola del recorrido por niveles puede crecer mucho más en un árbol completo que en un árbol degenerado?.

    En `travLevel`, la cola puede contener gran parte de un nivel completo; en un árbol completo, la última capa puede ocupar aproximadamente la mitad de los nodos del árbol.

#### Bloque 4 - Demostración: evidencia observable

Revisa y ejecuta:

- `Semana5/demos/demo_binary_tree.cpp`
- `Semana5/demos/demo_bst.cpp`
- `Semana5/demos/demo_heap.cpp`
- `Semana5/demos/demo_capitulo5_panorama.cpp`

Construye una tabla con cuatro columnas:

- Archivo
- Salida u observable importante
- Idea estructural
- Argumento de costo, espacio o diseño

Luego responde:

1. En `demo_binary_tree.cpp`, ¿qué salida permite verificar que los recorridos visitan los nodos en el orden esperado?
2. ¿Qué parte de la demo permite defender que `succ()` y `pred()` respetan el orden inorden?
3. ¿Qué evidencia produce la representación ASCII del árbol?
4. En `demo_bst.cpp`, ¿qué observable permite defender que el inorden del BST queda ordenado?
5. ¿Qué operaciones de búsqueda se distinguen mejor en la demo del BST: `find`, `findEQ`, `lowerBound` o `upperBound`?
6. En `demo_heap.cpp`, ¿qué salida permite defender que el mínimo queda en la raíz?
7. ¿Qué evidencia permite distinguir entre insertar con `add()` y construir con `heapify()`?
8. En `demo_capitulo5_panorama.cpp`, ¿qué comparación resume mejor la semana: árbol enlazado, BST o heap?.

#### Bloque 5 - Pruebas públicas, pruebas internas e invariantes

Revisa:

- `Semana5/pruebas_publicas/test_public_week5.cpp`
- `Semana5/pruebas_internas/test_internal_week5.cpp`

Responde:

1. ¿Qué operaciones del BST valida la prueba pública?
2. ¿Qué casos validan que el BST no acepta duplicados?
3. ¿Qué se verifica al comparar el inorden recursivo con las versiones iterativas?
4. ¿Qué se espera de `findEQ(8)` en la prueba pública?
5. ¿Qué se espera de `lowerBound(9)` y `upperBound(8)`?
6. ¿Qué propiedad se valida con `isBST()`?
7. ¿Qué se valida después de eliminar un nodo con `remove()`?
8. ¿Qué valida `checkParentLinks()` después de borrar, separar o adjuntar subárboles?
9. ¿Qué operaciones del heap valida la prueba pública?
10. ¿Qué demuestra extraer repetidamente de un min-heap hasta vaciarlo?
11. ¿Qué operaciones de `BinTree` se validan con `attachAsRC`, `secede` y `removeSubtree`?
12. ¿Qué agregan las pruebas internas respecto a rotaciones, `bubbleUp`, `trickleDown`, profundidad, altura, sucesor y predecesor?
13. ¿Qué sí demuestra pasar las pruebas públicas?
14. ¿Qué no demuestra pasar las pruebas públicas?
15. ¿Por qué una defensa correcta debe mencionar invariantes y complejidad además de resultados observables?.


#### Bloque 6 - Lectura cercana: `BinNode`, `BinTree` y `BinaryTree`

Revisa:

- `Semana5/include/BinNode.h`
- `Semana5/include/BinTree.h`
- `Semana5/include/BinaryTree.h`

Responde:

1. En `BinNode`, ¿qué invariantes deben mantenerse entre `parent`, `left` y `right`?
2. ¿Por qué `insertAsLC` e `insertAsRC` deben rechazar una inserción cuando el hijo correspondiente ya existe?
3. Explica cómo `size()` de `BinNode` recorre el subárbol.
4. Explica cómo funcionan `leftmost()` y `rightmost()`.
5. Explica paso a paso cómo funciona `succ()`.
6. Explica paso a paso cómo funciona `pred()`.
7. En `BinTree`, ¿qué papel cumplen `root_` y `size_`?
8. Explica qué hace `updateHeight(Node*)`.
9. Explica qué hace `updateHeightAbove(Node*)` y por qué sube hacia la raíz.
10. Explica cómo `attachAsLC` o `attachAsRC` transfieren un subárbol desde un árbol hacia otro.
11. Explica qué diferencia hay entre `removeSubtree` y `secede`.
12. Explica por qué `secede` no debe destruir los nodos desprendidos.
13. Explica por qué `removeSubtree` sí debe liberar nodos.
14. Explica qué verifica `checkParentLinks()`.
15. En `BinaryTree`, explica cómo se implementan `firstNode`, `lastNode`, `nextNode` y `prevNode`.
16. Explica por qué un iterador basado en `succ()` produce recorrido inorden.
17. Explica qué aporta `asciiArt()` para depuración y sustentación.


#### Bloque 7 - Árbol binario de búsqueda: búsqueda, eliminación y rotaciones

Revisa:

- `Semana5/include/BinarySearchTree.h`
- `Semana5/demos/demo_bst.cpp`
- `Semana5/pruebas_publicas/test_public_week5.cpp`
- `Semana5/pruebas_internas/test_internal_week5.cpp`

Responde:

1. Define formalmente la propiedad BST.
2. Explica por qué el recorrido inorden de un BST debe producir una secuencia no decreciente.
3. Explica la diferencia entre `find`, `findEQ`, `lowerBound` y `upperBound`.
4. Explica por qué `findEQ(x)` puede fallar aunque `lowerBound(x)` no falle.
5. Construye manualmente el BST que se obtiene al insertar: `7, 3, 10, 1, 5, 8, 12, 4, 6`.
6. Escribe el inorden, preorden, postorden y recorrido por niveles de ese árbol.
7. Simula `lowerBound(9)` y `upperBound(8)` paso a paso.
8. Explica qué casos de eliminación existen en un BST: hoja, un hijo, dos hijos.
9. Explica qué papel cumple `splice` durante una eliminación.
10. Después de eliminar una clave, ¿qué invariantes deben seguir siendo ciertos?
11. Explica por qué `remove(3)` en las pruebas debe conservar el inorden ordenado.
12. Explica qué hace `rotateLeft`.
13. Explica qué hace `rotateRight`.
14. Demuestra que una rotación local preserva la propiedad BST.
15. Explica para qué sirve construir un BST balanceado desde un arreglo ordenado.
16. Compara el costo de búsqueda en un BST balanceado y en un BST degenerado.


#### Bloque 8 - Heap binario y representación implícita

Revisa:

- `Semana5/include/BinaryHeap.h`
- `Semana5/demos/demo_heap.cpp`
- `Semana5/pruebas_publicas/test_public_week5.cpp`
- `Semana5/pruebas_internas/test_internal_week5.cpp`

Responde:

1. Explica por qué un heap binario puede almacenarse en un `std::vector` sin punteros.
2. Demuestra las fórmulas:

   ```cpp
   left(i) = 2*i + 1
   right(i) = 2*i + 2
   parent(i) = (i - 1) / 2
   ```

3. Define la propiedad de min-heap.
4. Explica por qué `top()` devuelve el mínimo.
5. Explica paso a paso cómo `bubbleUp(i)` restaura la propiedad de heap después de insertar.
6. Explica paso a paso cómo `trickleDown(i)` restaura la propiedad de heap después de eliminar la raíz.
7. Explica por qué `remove()` debe mover el último elemento a la raíz antes de aplicar `trickleDown(0)`.
8. Explica qué verifica `isHeap()`.
9. Compara construir un heap insertando `n` elementos con construirlo usando `heapify()`.
10. Justifica por qué insertar `n` elementos uno por uno cuesta `O(n log n)` en el peor caso.
11. Justifica por qué `heapify()` puede ejecutarse en `O(n)`.
12. Ejecuta una extracción completa del heap construido con `{7, 3, 10, 1, 5, 8, 2}` y explica por qué la secuencia extraída sale ordenada.
13. Compara el heap con el BST: ¿cuál estructura conviene para consultar mínimo repetidamente y cuál conviene para búsquedas ordenadas?.


#### Bloque 9 - Cierre comparativo y preparación de sustentación

Responde esta pregunta final:

¿Qué cambia cuando pasamos de estudiar listas, pilas y colas a diseñar árboles binarios, heaps y árboles binarios de búsqueda?

La respuesta debe incluir obligatoriamente:

- Una afirmación sobre representación enlazada con nodos y punteros.
- Una afirmación sobre representación implícita en arreglo.
- Una afirmación sobre la diferencia entre propiedad estructural y propiedad de orden.
- Una afirmación sobre recorridos y por qué son una forma de convertir un árbol en una secuencia.
- Una afirmación sobre mantenimiento de alturas y enlaces `parent`.
- Una afirmación sobre BST, búsqueda ordenada y recorrido inorden.
- Una afirmación sobre heap, prioridad y costo de `add`, `remove` y `heapify`.
- Una afirmación sobre qué evidencia usarías para defender correctitud: pruebas, demos, invariantes, trazados y complejidad.