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

   Un árbol binario enlazado guarda nodos como objetos con punteros `parent`, `left` y `right`, mientras que un árbol implícito usa un arreglo donde la relación padre-hijo se calcula por índices. En `Semana5/include/BinNode.h` líneas 23-26 se declara la estructura enlazada, y en `Semana5/include/BinaryHeap.h` líneas 23-25 se declaran las funciones `left(i)`, `right(i)` y `parent(i)`.

2. Explica qué información guarda un `BinNode`: dato, padre, hijo izquierdo, hijo derecho y altura.

   Un `BinNode` almacena el dato y los enlaces necesarios para la navegación y el mantenimiento: `data`, `parent`, `left`, `right` y `height`. Esto permite recorrer el árbol, calcular sucesores/predecesores y actualizar alturas. Está en `Semana5/include/BinNode.h` líneas 23-26.

3. Explica por qué el puntero `parent` permite implementar operaciones como `succ()`, `pred()` y actualización ascendente de alturas.

   El puntero `parent` permite subir desde cualquier nodo hacia la raíz, lo que hace posible implementar `succ()` y `pred()` sin recorrer todo el árbol. Además, `updateHeightAbove()` usa `parent` para propagar cambios de altura hacia arriba. En `Semana5/include/BinNode.h` líneas 94-109 y 124-139 se ve `succ()` y `pred()`, y en `Semana5/include/BinTree.h` línea 74 `updateHeightAbove` recorre `parent` hacia la raíz.

4. Explica qué responsabilidad tiene `BinTree` frente a `BinNode`.

   `BinTree` se encarga de la gestión global del árbol: mantiene `root_`, `size_`, crea y elimina nodos, y coordina operaciones como insertar, adjuntar subárboles y recorrer el árbol. La lógica general está en `Semana5/include/BinTree.h` líneas 74-136.

5. Explica qué agrega `BinaryTree` sobre la infraestructura base de `BinTree`.

   `BinaryTree` añade sobre `BinTree` los iteradores en inorden, la navegación con `firstNode`, `lastNode`, `nextNode`, `prevNode`, y herramientas de depuración como `asciiArt()`. Estas funciones están en `Semana5/include/BinaryTree.h` líneas 19-149.

6. Explica qué propiedad adicional convierte un árbol binario en un `BinarySearchTree`.

   La propiedad adicional que convierte un árbol binario en BST es que para cada nodo, todos los valores del subárbol izquierdo son menores y los valores del subárbol derecho son mayores. Esto se implementa en `Semana5/include/BinarySearchTree.h` líneas 40-70 con `findLast`, `findEQ`, `lowerBound`, `upperBound` y `addChild`.

7. Explica qué propiedad adicional convierte un arreglo en un `BinaryHeap` mínimo.

   Un arreglo es un `BinaryHeap` mínimo cuando cada elemento cumple la invariante padre≤hijo. En `Semana5/include/BinaryHeap.h` línea 101 `isHeapArray` comprueba esta relación local en todo el arreglo.

8. Compara la propiedad de orden de un BST con la propiedad de prioridad de un heap.

   En un BST la propiedad de orden es global: permite búsquedas ordenadas a lo largo de todo el árbol. En un heap la propiedad de prioridad es local: garantiza solo que la raíz es el mínimo y cada padre es menor que sus hijos. Por eso un BST sirve para búsquedas y rangos, y un heap sirve para extraer el mínimo rápidamente.

9. Explica por qué un recorrido inorden de un BST produce una secuencia ordenada.

   El recorrido inorden de un BST produce una secuencia ordenada porque explora el subárbol izquierdo primero, luego el nodo actual, luego el subárbol derecho. Esa secuencia está garantizada por la propiedad de orden del BST y se ve en `BinNode::travInRecursive` y `BinaryTree::traverseInorder`.

10. Explica por qué un heap no permite, por sí solo, recorrer los elementos en orden sin destruir o copiar la estructura.

    Un heap no permite recorrer elementos en orden sin destruirlo o copiarlo porque su invariante no ordena hermanos entre sí; solo asegura prioridad padre-hijo. Por eso para obtener orden completo hay que extraer repetidamente el mínimo.

#### Bloque 2 - Navegación, altura, profundidad y tamaño

Revisa:

- `Semana5/include/BinNode.h`
- `Semana5/include/BinTree.h`
- `Semana5/include/BinaryTree.h`
- `Semana5/demos/demo_binary_tree.cpp`

Responde:

1. En `BinNode`, explica qué significan `hasLeft()`, `hasRight()`, `isRoot()`, `isLeaf()`, `isLeftChild()` e `isRightChild()`.

   En `BinNode.h`, `hasLeft()`/`hasRight()` indican si existen hijos directo; `isRoot()` indica raíz; `isLeaf()` indica ausencia de hijos; `isLeftChild()`/`isRightChild()` verifican si el nodo es el hijo izquierdo o derecho de su padre. Estas funciones hacen más segura la navegación y las rotaciones.

2. Explica el caso en que `succ()` baja al subárbol derecho y luego busca el nodo más a la izquierda.

   En `succ()`, si el nodo tiene hijo derecho, el sucesor es el nodo más a la izquierda de ese subárbol derecho. Ese caso aparece claramente en `Semana5/include/BinNode.h` línea 94.

3. Explica el caso en que `succ()` sube por los ancestros hasta encontrar el primer giro hacia la izquierda.

   Si no hay hijo derecho, `succ()` sube por `parent` hasta encontrar el primer ancestro cuya rama se alcanzó desde su hijo izquierdo; ese ancestro es el sucesor. Esto se ve en el bucle `while (s->isRightChild()) { s = s->parent; } return s->parent;`.

4. Explica simétricamente cómo debe funcionar `pred()`.

   `pred()` es simétrico: si hay hijo izquierdo, baja al `rightmost()` de ese subárbol izquierdo; si no, sube hasta el primer ancestro alcanzado desde su hijo derecho. Esto está en `Semana5/include/BinNode.h` línea 124.

5. Dibuja un árbol de al menos 7 nodos y marca el sucesor y predecesor inorden de tres nodos distintos.

   ```
            7
         /    \
        3      10
      /  \    /  \
     1    5  8   12
        /  \
       4    6
   ```

   En ese árbol, el sucesor de 3 es 4 o 5 según el camino, el predecesor de 8 es 7 y el sucesor de 5 es 6.

6. Explica qué calcula `depth(u)` y por qué puede implementarse subiendo por `parent`.

   `depth(u)` cuenta ancestros desde `u` hasta la raíz usando `parent`; es una métrica de cuánto se ha descendido. Esto se implementa en `Semana5/include/BinaryTree.h` línea 76.

7. Explica qué calcula `height(u)` y por qué suele implementarse bajando recursivamente por los hijos.

   `height(u)` mide el número máximo de niveles desde `u` hasta una hoja y se calcula recursivamente por hijas. Esto está en `Semana5/include/BinaryTree.h` línea 85.

8. Explica qué calcula `subtreeSize(u)`.

   `subtreeSize(u)` suma el tamaño de los subárboles izquierdo y derecho más el nodo actual, recurriendo en cada hijo. Está en `Semana5/include/BinaryTree.h` línea 96.

9. Demuestra que para todo nodo `u` se cumple `depth(u) + height(u) <= height(T)`.

   La desigualdad `depth(u)+height(u) <= height(T)` se cumple porque cualquier camino raíz→hoja que pasa por `u` se compone de la distancia raíz→`u` más la distancia `u`→hoja, y esto no puede superar la altura total del árbol.

10. Indica la condición necesaria y suficiente para que se alcance la igualdad anterior.

    La igualdad ocurre cuando `u` está en una rama máxima del árbol, es decir, cuando `u` pertenece a un camino de longitud igual a la altura del árbol.

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

| Recorrido | Versión revisada | Estructura auxiliar usada | Secuencia producida | Argumento de correctitud y costo |
|---|---|---|---|---|
| preorden recursivo | `travPre` | pila de llamadas | `7 3 1 5 4 6 10 8 12` | Visita nodo antes de hijos; exactamente un paso por nodo; O(n). |
| preorden iterativo | `travPreIterative2` | `std::stack<Node*>` | `7 3 1 5 4 6 10 8 12` | Simula recursión con pila explícita; el orden se mantiene al apilar primero el hijo derecho. |
| inorden recursivo | `travInRecursive` | pila de llamadas | `1 3 4 5 6 7 8 10 12` | Garantiza izquierda-nodo-derecha; O(n) porque cada nodo se procesa una vez. |
| inorden iterativo #1 | `travInIterative1` | `std::stack<Node*>` | `1 3 4 5 6 7 8 10 12` | Usa pila para bajar al extremo izquierdo y luego subir; todo nodo entra y sale una vez. |
| inorden iterativo #2 | `travInIterative2` | punteros `prev`/`curr` | `1 3 4 5 6 7 8 10 12` | Recorrido sin pila explícita adicional, solo mantiene estado de movimiento. |
| inorden iterativo #3 | `travInIterative3` | otra variante de pila | `1 3 4 5 6 7 8 10 12` | Alternativa iterativa que usa control explícito similar a un DFA. |
| postorden recursivo | `travPost` | pila de llamadas | `1 4 6 5 3 8 12 10 7` | Visita hijos antes del nodo; útil para liberación de memoria. |
| postorden iterativo | `travPostIterative` | pila(s) | `1 4 6 5 3 8 12 10 7` | Simula recursión con estructura extra; O(n). |
| recorrido por niveles | `travLevel` | `std::queue<Node*>` | `7 3 10 1 5 8 12 4 6` | Usa cola para procesar por distancia a la raíz; O(n). |

Luego responde:

1. ¿Qué significa visitar un nodo en preorden?

   Visitar un nodo en preorden significa procesarlo antes de explorar sus hijos. Es implementado en: `travPre` de la cabecera `BinNode.h` en las lineas 155-160.

2. ¿Qué significa visitar un nodo en inorden?

   Visitar un nodo en inorden significa procesar primero su subárbol izquierdo, luego el nodo, luego su subárbol derecho. Es implementado en: `travInRecursive` de la cabecera `BinNode.h` en las lineas 183-191, y variantes iterativas `travInIterative1` en las lineas 194-206, `travInIterative2` en las lineas 210-230, `travInIterative3` en las lineas 234-242.

3. ¿Qué significa visitar un nodo en postorden?

   Visitar un nodo en postorden significa procesar primero ambos subárboles y luego el nodo. Es implementado en: `travPost` de la cabecera `BinNode.h` en las lineas 260-268 y versión iterativa `travPostIterative` en las lineas 271-289.

4. ¿Qué significa visitar un árbol por niveles?

   Visitar un árbol por niveles significa recorrer los nodos por capas, de la raíz hacia abajo. Es implementado en: `travLevel` de la cabecera `BinNode.h` en las lineas 293-307 que usa `std::queue`.

5. ¿Por qué los recorridos recursivos tienen tiempo `O(n)`?

   Porque cada nodo se visita una vez en la recursión y el trabajo por nodo es constante. Es implementado en: `travInRecursive` en las lineas 183-191.

6. ¿Por qué las versiones iterativas también tienen tiempo `O(n)`?

   Porque cada nodo y cada enlace entran y salen de la estructura auxiliar (pila/cola) un número acotado de veces. Es implementado en: `travInIterative1` en las lineas 194-206 y `travPostIterative` en las lineas 271-289.

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

   En `demo_binary_tree.cpp`, la salida que verifica los recorridos es la impresión de los nodos en el orden esperado para preorden, inorden, postorden y por niveles.
   Es implementado en: `travInRecursive`, `travPre`, `travPost`, `travLevel` de la cabecera `BinNode.h` en las líneas 155-160, 183-191, 260-268 y 293-307.

2. ¿Qué parte de la demo permite defender que `succ()` y `pred()` respetan el orden inorden?

   La parte que defiende `succ()` y `pred()` es la prueba de sucesor/predecesor en la demo, donde se imprime el siguiente y el anterior de nodos concretos.
   Es implementado en: `succ()` y `pred()` de `BinNode.h` en las líneas alrededor de 94-109 y 124-139.

3. ¿Qué evidencia produce la representación ASCII del árbol?

   La representación ASCII del árbol produce evidencia visual de la estructura enlazada y la relación padre-hijo.
   Es implementado en: `asciiArt()` de `BinaryTree.h` en las líneas aproximadas 85-149.

4. En `demo_bst.cpp`, ¿qué observable permite defender que el inorden del BST queda ordenado?

   En `demo_bst.cpp`, el observable que defiende el inorden ordenado es la salida del recorrido inorden del BST.
   Es implementado en: `travInRecursive` y `travInIterative1`/`travInIterative2`/`travInIterative3` de `BinNode.h` en las líneas 183-242, y la llamada desde `BinaryTree` en `BinaryTree.h`.

5. ¿Qué operaciones de búsqueda se distinguen mejor en la demo del BST: `find`, `findEQ`, `lowerBound` o `upperBound`?

   En la demo del BST, las operaciones de búsqueda que se distinguen mejor son `findEQ`, `lowerBound` y `upperBound`, porque se presentan resultados de búsquedas exactas y de rango.
   Es implementado en: `BinarySearchTree.h` alrededor de las líneas 40-70.

6. En `demo_heap.cpp`, ¿qué salida permite defender que el mínimo queda en la raíz?

   En `demo_heap.cpp`, la salida que permite defender que el mínimo queda en la raíz es el valor impreso por `top()` después de construir el heap.
   Es implementado en: `BinaryHeap.h`, método `top()` y `heapify()`.

7. ¿Qué evidencia permite distinguir entre insertar con `add()` y construir con `heapify()`?

   La evidencia que distingue `add()` de `heapify()` es la comparación entre construir el heap elemento a elemento y construirlo desde un arreglo completo.
   Es implementado en: `BinaryHeap.h` con `add()` (`bubbleUp`) y `heapify()` (`trickleDown`).

8. En `demo_capitulo5_panorama.cpp`, ¿qué comparación resume mejor la semana: árbol enlazado, BST o heap?.

   En `demo_capitulo5_panorama.cpp`, la comparación que resume mejor la semana es que el BST es adecuado para búsqueda ordenada y consultas de rango, mientras que el heap es adecuado para prioridad mínima y extracción eficiente del mínimo.
   Es implementado en: demo y en los archivos `BinaryTree.h`, `BinarySearchTree.h`, `BinaryHeap.h`.

#### Bloque 5 - Pruebas públicas, pruebas internas e invariantes

Revisa:

- `Semana5/pruebas_publicas/test_public_week5.cpp`
- `Semana5/pruebas_internas/test_internal_week5.cpp`

Responde:

1. ¿Qué operaciones del BST valida la prueba pública?

   La prueba pública valida operaciones del BST como `add()`, `findEQ()`, `lowerBound()`, `upperBound()`, `remove()` y recorridos.

2. ¿Qué casos validan que el BST no acepta duplicados?

   Verifica duplicados al intentar insertar una clave ya existente y confirmar que `add()` devuelve falso.

3. ¿Qué se verifica al comparar el inorden recursivo con las versiones iterativas?

   Comparar inorden recursivo con versiones iterativas valida que todas las implementaciones generan la misma secuencia ordenada.

4. ¿Qué se espera de `findEQ(8)` en la prueba pública?

   Se espera que `findEQ(8)` encuentre un nodo con dato `8`.

5. ¿Qué se espera de `lowerBound(9)` y `upperBound(8)`?

   Se espera que `lowerBound(9)` devuelva `10` y que `upperBound(8)` devuelva `10`.

6. ¿Qué propiedad se valida con `isBST()`?

   `isBST()` valida que la estructura cumple la propiedad BST y que los enlaces de hijo/padre son consistentes.

7. ¿Qué se valida después de eliminar un nodo con `remove()`?

   Después de `remove()`, se valida que la clave eliminada desaparece del inorden y que el árbol sigue ordenado.

8. ¿Qué valida `checkParentLinks()` después de borrar, separar o adjuntar subárboles?

   `checkParentLinks()` verifica que todos los `parent` de los nodos sean correctos después de adjuntar, desprender o eliminar subárboles.

9. ¿Qué operaciones del heap valida la prueba pública?

   La prueba pública del heap valida `add()`, `remove()` y `isHeap()`.

10. ¿Qué demuestra extraer repetidamente de un min-heap hasta vaciarlo?

    Extraer repetidamente un min-heap y verificar la secuencia resultante demuestra que el heap devuelve valores en orden no decreciente.

11. ¿Qué operaciones de `BinTree` se validan con `attachAsRC`, `secede` y `removeSubtree`?

    `attachAsRC`, `secede` y `removeSubtree` validan operaciones de estructura, tamaño y mantenimiento de enlaces al transferir o destruir subárboles.

12. ¿Qué agregan las pruebas internas respecto a rotaciones, `bubbleUp`, `trickleDown`, profundidad, altura, sucesor y predecesor?

    Las pruebas internas cubren rotaciones, `bubbleUp`, `trickleDown`, actualización de alturas y navegación con `succ`/`pred`.

13. ¿Qué sí demuestra pasar las pruebas públicas?

    Pasar las pruebas públicas demuestra que los casos básicos y comunes del BST y heap funcionan correctamente.   

14. ¿Qué no demuestra pasar las pruebas públicas?

    No demuestra todos los casos límite ni la eficiencia en cada configuración posible.

15. ¿Por qué una defensa correcta debe mencionar invariantes y complejidad además de resultados observables?.

    Una defensa correcta debe mencionar invariantes y complejidad porque las pruebas muestran resultados, pero las invariantes y el análisis explican por qué esos resultados son correctos y eficientes.

#### Bloque 6 - Lectura cercana: `BinNode`, `BinTree` y `BinaryTree`

Revisa:

- `Semana5/include/BinNode.h`
- `Semana5/include/BinTree.h`
- `Semana5/include/BinaryTree.h`

Responde:

1. En `BinNode`, ¿qué invariantes deben mantenerse entre `parent`, `left` y `right`?

   En `BinNode`, los invariantes son: si `parent == nullptr`, el nodo es raíz; si `left` o `right` existe, su `parent` debe apuntar al nodo; los hijos no deben apuntar a nodos incompatibles. Esto evita roturas en la navegación.

2. ¿Por qué `insertAsLC` e `insertAsRC` deben rechazar una inserción cuando el hijo correspondiente ya existe?

   `insertAsLC` e `insertAsRC` deben rechazar la inserción cuando el hijo ya existe para no perder subárboles ni violar la estructura binaria.

3. Explica cómo `size()` de `BinNode` recorre el subárbol.

   `size()` de `BinNode` recorre recursivamente el subárbol sumando 1 + tamaño izquierdo + tamaño derecho.

4. Explica cómo funcionan `leftmost()` y `rightmost()`.

   `leftmost()` y `rightmost()` bajan por los hijos izquierdo o derecho hasta la hoja correspondiente.

5. Explica paso a paso cómo funciona `succ()`.

   `succ()` busca el siguiente nodo en inorden: si hay hijo derecho, va al mínimo de ese subárbol; si no, sube por `parent` hasta encontrar el primer ancestro alcanzado desde su hijo izquierdo.

6. Explica paso a paso cómo funciona `pred()`.

   `pred()` hace lo simétrico: si hay hijo izquierdo, va al máximo de ese subárbol; si no, sube hasta el primer ancestro alcanzado desde un hijo derecho.

7. En `BinTree`, ¿qué papel cumplen `root_` y `size_`?

   En `BinTree`, `root_` mantiene la raíz y `size_` el número de nodos del árbol.

8. Explica qué hace `updateHeight(Node*)`.

   `updateHeight(Node*)` recalcula la altura de un nodo a partir de las alturas de sus hijos.

9. Explica qué hace `updateHeightAbove(Node*)` y por qué sube hacia la raíz.

   `updateHeightAbove(Node*)` sube hacia la raíz actualizando alturas en todos los ancestros hasta que no haya cambios.

10. Explica cómo `attachAsLC` o `attachAsRC` transfieren un subárbol desde un árbol hacia otro.

    `attachAsLC`/`attachAsRC` transfieren un subárbol de un árbol a otro ajustando `parent`, `root_`, `size_` y alturas.

11. Explica qué diferencia hay entre `removeSubtree` y `secede`.

    `removeSubtree` destruye un subárbol liberando nodos, mientras que `secede` lo separa sin destruirlo.

12. Explica por qué `secede` no debe destruir los nodos desprendidos.

    `secede` no debe destruir los nodos desprendidos porque el subárbol sigue siendo válido como árbol independiente.

13. Explica por qué `removeSubtree` sí debe liberar nodos.

    `removeSubtree` debe liberar nodos porque se está eliminando la estructura de memoria.

14. Explica qué verifica `checkParentLinks()`.

    `checkParentLinks()` verifica que todos los enlaces `parent` sean correctos después de modificaciones.

15. En `BinaryTree`, explica cómo se implementan `firstNode`, `lastNode`, `nextNode` y `prevNode`.

    En `BinaryTree`, `firstNode`, `lastNode`, `nextNode` y `prevNode` se implementan usando `leftmost`, `rightmost`, `succ` y `pred`.

16. Explica por qué un iterador basado en `succ()` produce recorrido inorden.

    Un iterador basado en `succ()` produce recorrido inorden porque `succ()` sigue la definición del siguiente nodo en inorden.

17. Explica qué aporta `asciiArt()` para depuración y sustentación.

    `asciiArt()` aporta depuración visual y hace más fácil defender la estructura del árbol durante la sustentación.

#### Bloque 7 - Árbol binario de búsqueda: búsqueda, eliminación y rotaciones

Revisa:

- `Semana5/include/BinarySearchTree.h`
- `Semana5/demos/demo_bst.cpp`
- `Semana5/pruebas_publicas/test_public_week5.cpp`
- `Semana5/pruebas_internas/test_internal_week5.cpp`

Responde:

1. Define formalmente la propiedad BST.

   La propiedad BST es: para todo nodo `u`, todos los valores en el subárbol izquierdo de `u` son menores que `u->data` y todos los valores en el subárbol derecho son mayores que `u->data`.

2. Explica por qué el recorrido inorden de un BST debe producir una secuencia no decreciente.

   El inorden de un BST produce una secuencia no decreciente porque visita primero todo el subárbol izquierdo, luego el nodo y luego el subárbol derecho.

3. Explica la diferencia entre `find`, `findEQ`, `lowerBound` y `upperBound`.

   `find` busca una clave igual o reporta ausencia, `findEQ` busca exactamente esa clave, `lowerBound` devuelve el primer valor ≥ x y `upperBound` devuelve el primer valor > x.

4. Explica por qué `findEQ(x)` puede fallar aunque `lowerBound(x)` no falle.

   `findEQ(x)` puede fallar aunque `lowerBound(x)` no, porque puede no existir ningún elemento igual a `x`; en ese caso `lowerBound(x)` devuelve el siguiente mayor.

5. Construye manualmente el BST que se obtiene al insertar: `7, 3, 10, 1, 5, 8, 12, 4, 6`.

   Al insertar `7, 3, 10, 1, 5, 8, 12, 4, 6`, el BST tiene raíz 7, izquierda 3 con hijos 1 y 5, derecha 10 con hijos 8 y 12, y 5 con hijos 4 y 6.

6. Escribe el inorden, preorden, postorden y recorrido por niveles de ese árbol.

   Inorden: `1 3 4 5 6 7 8 10 12`; preorden: `7 3 1 5 4 6 10 8 12`; postorden: `1 4 6 5 3 8 12 10 7`; por niveles: `7 3 10 1 5 8 12 4 6`.

7. Simula `lowerBound(9)` y `upperBound(8)` paso a paso.

   `lowerBound(9)` sigue la rama derecha desde 7 y devuelve 10; `upperBound(8)` sigue 7→10 y devuelve 10.

8. Explica qué casos de eliminación existen en un BST: hoja, un hijo, dos hijos.

   Eliminación en BST tiene tres casos: hoja, nodo con un hijo y nodo con dos hijos.

9. Explica qué papel cumple `splice` durante una eliminación.

   `splice` reemplaza un nodo con su único hijo y actualiza padre y altura.

10. Después de eliminar una clave, ¿qué invariantes deben seguir siendo ciertos?

    Después de eliminar, deben mantenerse la propiedad BST, los enlaces `parent` correctos y las alturas actualizadas.

11. Explica por qué `remove(3)` en las pruebas debe conservar el inorden ordenado.

    `remove(3)` debe conservar el inorden ordenado porque en el caso de dos hijos se reemplaza con el sucesor inorden y se mantiene la estructura ordenada.

12. Explica qué hace `rotateLeft`.

    `rotateLeft` mueve la raíz de un subárbol hacia la izquierda y promueve su hijo derecho.

13. Explica qué hace `rotateRight`.

    `rotateRight` es simétrico: mueve la raíz hacia la derecha y promueve su hijo izquierdo.

14. Demuestra que una rotación local preserva la propiedad BST.

    Una rotación local preserva la propiedad BST porque reordena subárboles contiguos sin cambiar el orden relativo de los valores.

15. Explica para qué sirve construir un BST balanceado desde un arreglo ordenado.

    Construir un BST balanceado desde un arreglo ordenado produce altura mínima y mejor costo de búsqueda.

16. Compara el costo de búsqueda en un BST balanceado y en un BST degenerado.

    En un **árbol binario de búsqueda (BST)** balanceado, la altura es aproximadamente $log(n)$, lo que permite descartar la mitad de los nodos en cada paso y realizar búsquedas en tiempo $O(log(n))$; en cambio, cuando el árbol está **degenerado** es decir, se convierte en una lista enlazada porque cada nodo tiene solo un hijo la altura pasa a ser $n$, obligando a recorrer nodo por nodo hasta encontrar el valor y haciendo que la búsqueda tenga un costo de $O(n)$, perdiendo así la eficiencia característica de los BST.


#### Bloque 8 - Heap binario y representación implícita

Revisa:

- `Semana5/include/BinaryHeap.h`
- `Semana5/demos/demo_heap.cpp`
- `Semana5/pruebas_publicas/test_public_week5.cpp`
- `Semana5/pruebas_internas/test_internal_week5.cpp`

Responde:

1. Explica por qué un heap binario puede almacenarse en un `std::vector` sin punteros.

   Un heap binario puede almacenarse en `std::vector` porque las relaciones padre-hijo se calculan por índice: izquierda `2*i+1`, derecha `2*i+2`, padre `(i-1)/2`.

2. Demuestra las fórmulas:

   ```cpp
   left(i) = 2*i + 1
   right(i) = 2*i + 2
   parent(i) = (i - 1) / 2
   ```

   Las fórmulas provienen de la representación de un **árbol binario** en un **arreglo**. Cada nodo ocupa una posición `i` en el array y sus relaciones se calculan aritméticamente:

   - **Hijo izquierdo:** `left(i) = 2*i + 1`  
     Se cumple porque al recorrer el árbol en orden por niveles, el primer hijo de un nodo en posición `i` aparece en la posición `2*i + 1`.  
     Ejemplo: para `i = 0` (la raíz), el hijo izquierdo está en `1`.

   - **Hijo derecho:** `right(i) = 2*i + 2`  
     El segundo hijo aparece inmediatamente después del izquierdo, en la posición `2*i + 2`.  
     Ejemplo: para `i = 0`, el hijo derecho está en `2`.

   - **Padre:** `parent(i) = (i - 1) / 2` (división entera)  
     Invirtiendo la fórmula, el padre de un nodo en posición `i` se obtiene restando 1 y dividiendo entre 2.  
     Ejemplo: para `i = 5`, el padre está en `(5 - 1)/2 = 2`.

3. Define la propiedad de min-heap.

   La propiedad de min-heap indica que en todo nodo del árbol binario, el valor del padre es siempre menor que el de sus hijos directos; esto asegura que el elemento mínimo esté en la raíz.

4. Explica por qué `top()` devuelve el mínimo.

   `top()` devuelve el mínimo porque el menor elemento siempre está en la raíz según la propiedad del heap.

5. Explica paso a paso cómo `bubbleUp(i)` restaura la propiedad de heap después de insertar.

   `bubbleUp(i)` compara el nodo con su padre y sube mientras sea menor, restaurando la propiedad tras insertar.

6. Explica paso a paso cómo `trickleDown(i)` restaura la propiedad de heap después de eliminar la raíz.

   `trickleDown(i)` compara el nodo con sus hijos y baja hacia el hijo menor, restaurando la propiedad tras eliminar la raíz.

7. Explica por qué `remove()` debe mover el último elemento a la raíz antes de aplicar `trickleDown(0)`.

   `remove()` mueve el último elemento a la raíz y luego aplica `trickleDown(0)` para restaurar el heap.

8. Explica qué verifica `isHeap()`.

   `isHeap()` verifica que el vector cumpla la propiedad de heap en todos los padres.

9. Compara construir un heap insertando `n` elementos con construirlo usando `heapify()`.

   Insertar `n` elementos uno por uno cuesta `O(n log n)` porque cada `add` inserta al final y puede requerir `bubbleUp` a través de `O(log n)` niveles.

10. Justifica por qué insertar `n` elementos uno por uno cuesta `O(n log n)` en el peor caso.

    `heapify()` puede ejecutarse en `O(n)` porque ajusta desde los nodos internos hacia la raíz, y los nodos más bajos requieren muy pocos intercambios; el costo amortizado sobre todos los nodos es lineal.

11. Justifica por qué `heapify()` puede ejecutarse en `O(n)`.

    Extraer completamente `{7, 3, 10, 1, 5, 8, 2}` produce la secuencia ordenada `1, 2, 3, 5, 7, 8, 10` porque cada extracción de `top()` devuelve el mínimo restante y luego `trickleDown` restablece la propiedad de heap.

12. Ejecuta una extracción completa del heap construido con `{7, 3, 10, 1, 5, 8, 2}` y explica por qué la secuencia extraída sale ordenada.

    Un heap es mejor para consultas repetidas del mínimo porque `top()` es `O(1)` y `remove()` es `O(log n)`; un BST es mejor para búsquedas ordenadas y consultas de rango porque puede recorrer sus elementos en orden con `O(n)` y buscar rangos en `O(h)`.

13. Compara el heap con el BST: ¿cuál estructura conviene para consultar mínimo repetidamente y cuál conviene para búsquedas ordenadas?.

    El **heap** es ideal cuando necesitamos consultar el mínimo repetidamente, ya que lo mantiene siempre en la raíz y permite acceder a él en tiempo constante, mientras que las operaciones de inserción y eliminación cuestan $O(log(n)); en cambio, el **BST** resulta más conveniente para búsquedas ordenadas, recorridos en secuencia creciente y consultas de rangos, gracias a su propiedad de orden y al recorrido inorden que devuelve los elementos en orden.


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

Cuando pasamos de estudiar listas, pilas y colas a diseñar árboles binarios, heaps y árboles binarios de búsqueda, el cambio está en que ya no trabajamos solo con estructuras lineales, sino con representación enlazada mediante nodos y punteros o con representación implícita en arreglos usando fórmulas de índices; además, debemos distinguir entre propiedad estructural (forma del árbol) y propiedad de orden (relación entre valores). Los recorridos como preorden, inorden o por niveles son clave porque convierten el árbol en una secuencia lineal procesable. También surge la necesidad de mantener alturas y enlaces `parent` para balancear y reorganizar. En un BST, la búsqueda ordenada se apoya en la propiedad de orden y el recorrido inorden devuelve los elementos en orden creciente; en un heap, la prioridad se asegura con la propiedad de heap y operaciones como `add`, `remove` y `heapify` tienen costo logarítmico. Finalmente, la correctitud de estas estructuras se defiende con evidencia como pruebas, demostraciones, invariantes, trazados de ejecución y análisis de complejidad.
