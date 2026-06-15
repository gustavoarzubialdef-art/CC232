## Actividad 7 - CC232

### Estudiante
- Nombre: GUSTAVO ANTHONY ARZUBIALDE FIERRO
- Código: 20230205H
- Fecha: 15/06/2026

#### Bloque 1 - Diagnóstico inicial de la Semana 7

Revisa:

* `Semana7/README.md`
* `Semana7/CMakeLists.txt`
* `Semana7/include/Capitulo7.h`

Ejecuta desde la raíz de la librería:

```bash
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug -R semana7 --output-on-failure
```

Responde:

1. ¿Qué targets de demostración aparecen para Semana 7?
2. ¿Qué pruebas públicas e internas aparecen?
3. ¿Qué archivos incluye `Capitulo7.h`?
4. ¿Qué relación conceptual hay entre Semana 5, Semana 6 y Semana 7?
5. ¿Por qué no es correcto decir que una carpeta "hereda" de otra carpeta?
6. ¿Qué clases sí usan herencia dentro del código?
7. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?.

Entrega en este bloque:

* Una tabla con comando ejecutado, resultado, error si hubo e interpretación.
* Una lista breve de los archivos que revisaste primero.

#### Bloque 2 - BST como punto de partida

Revisa:

* `Semana7/include/BST.h`
* `Semana7/include/BinarySearchTree.h`
* `Semana7/demos/demo_compare_with_semana5.cpp`
* `Semana7/demos/demo_bst_deng_vs_avl.cpp`

Responde:

1. Define formalmente la propiedad BST.
2. Explica por qué el recorrido inorder de un BST produce una secuencia ordenada.
3. Explica por qué insertar claves ordenadas puede producir un BST degenerado.
4. Construye manualmente el BST resultante de insertar:

```cpp
10, 20, 30, 40, 50, 60, 70
```

5. Indica la altura del árbol anterior si no hay balanceo.
6. Explica por qué una búsqueda en ese árbol puede costar `O(n)`.
7. Explica qué problema intenta resolver AVL.
8. Explica qué problema intenta resolver Red-Black Tree.

Entrega en este bloque:

* Dibujo del BST degenerado.
* Explicación breve de costo.
* Relación con Semana 5.

#### Bloque 3 - AVL: balance por altura

Revisa:

* `Semana7/include/AVL.h`
* `Semana7/include/BST.h`
* `Semana7/include/BinNode.h`
* `Semana7/demos/demo_avl_deng_core.cpp`

Responde:

1. ¿Qué significa que un nodo esté balanceado en un AVL?

   Un nodo está balanceado si la diferencia de alturas entre su hijo izquierdo y derecho está en el rango $[-1, 1]$. Esto garantiza que el árbol no se degrade a una estructura lineal.
   Implementación: `Semana7/include/AVL.h`, línea 63–66:
   ```cpp
   static bool avlBalanced(NodePosi x) {
     return -2 < balanceFactor(x) && balanceFactor(x) < 2;
   }
   ```
   Aquí se define que el nodo está balanceado si su factor de balance es mayor que -2 y menor que 2, lo que equivale a $[-1, 1]$.

2. ¿Cómo se calcula el factor de balance?

   El factor de balance mide la diferencia de alturas entre los subárboles izquierdo y derecho.
   Implementación: `Semana7/include/AVL.h`, línea 59–61:
   ```cpp
   static int balanceFactor(NodePosi x) {
     return stature(x->lc) - stature(x->rc);
   }
   ```
   Se resta la altura del hijo derecho a la del hijo izquierdo. Si el resultado es 0, el nodo está perfectamente balanceado.

3. ¿Qué información de altura debe mantenerse después de insertar o eliminar?

   Cada nodo guarda en su campo `height` la altura de su subárbol. Tras cada inserción o eliminación, esta altura debe recalcularse.
   Implementación: `Semana7/include/BinNode.h`, línea 38–40:
   ```cpp
   void updateHeight() { height = 1 + std::max(stature(lc), stature(rc)); }
   ```
   Esto asegura que la altura de un nodo sea siempre 1 más que la altura máxima de sus hijos.

4. ¿Qué representa `_hot` dentro de la implementación estilo Deng?

   `_hot` es un puntero que guarda el último nodo visitado en la búsqueda. Se usa como referencia para saber dónde insertar un nuevo nodo o desde dónde comenzar el rebalanceo tras eliminar.
   Implementación: `Semana7/include/BST.h`, línea 72:
   ```cpp
   NodePosi _hot{nullptr};
   ```

5. ¿Por qué AVL puede heredar de `BST<T, Compare>`?

   Un AVL es un BST con reglas adicionales de balance. Por eso reutiliza las operaciones básicas de búsqueda, inserción y eliminación del BST, y solo añade el rebalanceo.
   Implementación: `Semana7/include/AVL.h`, línea 9:
   ```cpp
   lass AVL : public BST<T, Compare> {
   ```

6. ¿Qué operación restaura localmente la forma del árbol?

   La operación clave es la rotación, que reorganiza nodos localmente para recuperar el balance.
   Implementación: `Semana7/include/BST.h`, línea 122–153:
   ```cpp
   NodePosi rotateAt(NodePosi v) {
     ...
   }
   ```
   Esta función aplica las rotaciones LL, RR, LR o RL según el caso.

7. ¿Por qué una rotación no destruye la propiedad BST?

   Porque las rotaciones preservan el orden inorder del árbol. Los elementos siguen apareciendo en orden creciente.
   Implementación: `Semana7/include/BST.h`, línea 106–120, función `connect34()`:
   ```cpp
   NodePosi connect34(NodePosi a, NodePosi b, NodePosi c,
                   NodePosi T0, NodePosi T1, NodePosi T2, NodePosi T3) {
     ...
   }
   ```
   Aquí se reacomodan los nodos y subárboles manteniendo el orden BST.

8. Después de insertar, ¿por qué suele bastar reparar el primer ancestro desbalanceado?

   La inserción afecta solo un camino desde la hoja hasta la raíz. El primer nodo desbalanceado encontrado es suficiente para restaurar el balance en todo el árbol.
   Implementación: `Semana7/include/AVL.h`, línea 27–31:
   ```cpp
   if (!avlBalanced(g)) {
     this->rotateAt(tallerChild(tallerChild(g)));
     break;
   }
   ```

9. Después de eliminar, ¿por qué puede ser necesario seguir revisando hacia la raíz?.

   La eliminación puede reducir la altura de varios subárboles, provocando nuevos desbalances en ancestros más arriba. Por eso se sigue revisando hasta la raíz.
   Implementación: `Semana7/include/AVL.h`, línea 44–51:
   ```cpp
   for (NodePosi g = this->_hot; g;) {
     if (!avlBalanced(g)) {
       NodePosi r = this->rotateAt(tallerChild(tallerChild(g)));
       g = r->parent;
     } else {
       this->updateHeight(g);
       g = g->parent;
     }
   }
   ```

Entrega en este bloque:

* Una explicación de los invariantes AVL.
* Un trazado de inserción con al menos una rotación.
* Evidencia de salida de `demo_avl_deng_core.cpp`.

#### Explicación de los invariantes AVL.

Un invariante es una condición que siempre debe cumplirse en la estructura de datos.
En el caso de los árboles AVL, los invariantes son:

1. Balance por altura:
   Para todo nodo, la diferencia de alturas entre su hijo izquierdo y derecho debe estar en el rango $[-1, 1]$.
   Esto asegura que el árbol nunca se degrade a una lista lineal y mantenga altura logarítmica.

2. Alturas actualizadas:
   Cada nodo guarda en su campo height la altura de su subárbol. Después de cada inserción o eliminación, se recalcula con:

   ```cpp
   void updateHeight() { height = 1 + std::max(stature(lc), stature(rc)); }
   ```
   (Archivo BinNode.h, línea 38–40).

3. Preservación del orden BST:
   Las rotaciones que se aplican para restaurar el balance no alteran el orden inorder del árbol.
   Esto significa que la propiedad de búsqueda binaria se mantiene intacta.

   En resumen: un AVL es un BST que garantiza balance estricto por altura en cada nodo.

#### Trazado de inserción con al menos una rotación.

Ejemplo: insertar los valores 30, 20, 10 en un AVL.

1. Insertar 30 → raíz.

   ```text
   30
   ```

2. Insertar 20 → hijo izquierdo de 30.

   ```text
     30
    /
   20
   ```

3. Insertar 10 → hijo izquierdo de 20.

   ```text
       30
      /
     20
    /
   10
   ```

   Aquí el nodo 30 queda desbalanceado (factor de balance = 2).
   Se aplica una rotación LL en 30:

   ```text
       30              20
      /               /  \
     20     →       10    30
    /
   10
   ```

   Resultado: el árbol vuelve a estar balanceado, cumpliendo los invariantes AVL.

#### Salida de `demo_avl_deng_core.cpp`.

```text
AVL inorder: 10 20 22 25 27 30 40 50
AVL level-order: 30 20 40 10 25 50 22 27
Valido AVL: si
Tras borrar 20 y 40: 10 22 25 27 30 50
Valido AVL: si
```

#### Bloque 4 - Rotaciones AVL: casos LL, RR, LR y RL

Revisa:

* `Semana7/include/AVLTreeCompact.h`
* `Semana7/demos/demo_avl_compact_rotations.cpp`
* `Semana7/include/AVL.h`

Ejecuta las demostraciones de rotaciones y construye una tabla con estas columnas:

* Caso
* Secuencia insertada
* Nodo desbalanceado
* Rotación aplicada
* Inorder antes
* Inorder después
* Altura final

Incluye los cuatro casos:

1. LL
2. RR
3. LR
4. RL

Responde:

1. ¿Qué diferencia hay entre una rotación simple y una rotación doble?
2. ¿Por qué LL y RR se corrigen con una sola rotación?
3. ¿Por qué LR y RL requieren dos pasos?
4. ¿Qué parte del árbol cambia y qué parte permanece igual?
5. ¿Por qué el inorder debe ser el mismo antes y después de reestructurar?.

Entrega en este bloque:

* Tabla de rotaciones.
* Cuatro dibujos pequeños.
* Argumento de preservación del orden BST.

#### Bloque 5 - Red-Black Tree: balance por colores

Revisa:

* `Semana7/include/RedBlackTree.h`
* `Semana7/include/BinarySearchTree.h`
* `Semana7/include/BinaryTree.h`
* `Semana7/demos/demo_redblack_morin.cpp`

Responde:

1. ¿Qué propiedad BST mantiene Red-Black Tree?
2. ¿Qué propiedades de color debe cumplir un Red-Black Tree?
3. ¿Por qué la raíz debe terminar negra?
4. ¿Qué significa que no pueda haber dos nodos rojos consecutivos?
5. ¿Qué representa la altura negra?
6. ¿Por qué Red-Black Tree permite un balance menos estricto que AVL?
7. ¿Qué correcciones pueden aparecer después de insertar?
8. ¿Qué correcciones pueden aparecer después de eliminar?
9. ¿Qué papel cumplen las rotaciones en Red-Black Tree?
10. ¿Qué papel cumple el cambio de colores?.

Entrega en este bloque:

* Lista de invariantes Red-Black.
* Explicación de una inserción que requiera recoloreo.
* Evidencia de salida de `demo_redblack_morin.cpp`.

#### Bloque 6 - Comparación: BST, Treap, AVL y Red-Black Tree

Revisa:

* `Semana6/include/Treap.h`
* `Semana7/demos/demo_compare_avl_vs_redblack.cpp`
* `Semana7/demos/demo_compare_with_semana5.cpp`
* `Semana7/demos/demo_capitulo7_panorama.cpp`

Construye una tabla con estas columnas:

* Estructura
* Propiedad de orden
* Propiedad adicional
* Operación de reparación
* Altura esperada o garantizada
* Caso donde conviene usarla

Incluye:

1. BST común
2. Treap
3. AVL
4. Red-Black Tree

Responde:

1. ¿Qué tienen en común BST, Treap, AVL y Red-Black Tree?
2. ¿Qué diferencia hay entre prioridad en Treap, altura en AVL y color en Red-Black Tree?
3. ¿Por qué Treap depende de prioridades?
4. ¿Por qué AVL suele ser más estricto en altura?
5. ¿Por qué Red-Black Tree puede ser preferible cuando hay muchas inserciones y eliminaciones?
6. ¿Qué estructura elegirías para defender búsqueda ordenada con balance fuerte?
7. ¿Qué estructura elegirías para explicar balance probabilístico?.

Entrega en este bloque:

* Tabla comparativa.
* Respuesta breve de decisión técnica.
* Conexión explícita con Semana 5 y Semana 6.

#### Bloque 7 - Pruebas, invariantes y defensa oral

Revisa:

* `Semana7/pruebas_publicas/test_public_week7.cpp`
* `Semana7/pruebas_internas/test_internal_week7.cpp`

Responde:

1. ¿Qué operaciones valida la prueba pública para AVL?
2. ¿Qué operaciones valida la prueba pública para Red-Black Tree?
3. ¿Qué casos adicionales cubre la prueba interna?
4. ¿Qué significa que una prueba valide el inorder?
5. ¿Qué significa que una prueba valide alturas o factores de balance?
6. ¿Qué significa que una prueba valide colores?
7. ¿Qué no demuestra pasar solo las pruebas públicas?
8. ¿Qué evidencia usarías en una sustentación: demostración, prueba, trazado o argumento de complejidad?
9. ¿Qué invariante revisarías primero si falla AVL?
10. ¿Qué invariante revisarías primero si falla Red-Black Tree?.

Entrega en este bloque:

* Tabla de pruebas revisadas.
* Lista de invariantes que defenderías.
* Evidencia de ejecución de `ctest`.

#### Bloque 8 - Ejercicios de codificación

En este bloque debes modificar o extender la Semana 7 sin romper la interfaz principal de la librería. El objetivo es comprobar que entiendes los invariantes de AVL y Red-Black Tree no solo de forma teórica, sino también mediante código, pruebas y evidencia de ejecución.

#### Ejercicio 1 - Validador de propiedad BST

Crea un archivo:

```bash
Semana7/demos/demo_validate_bst_property.cpp
```

Implementa una función auxiliar que valide si un árbol cumple la propiedad BST usando límites inferiores y superiores.

Firma sugerida:

```cpp
template <typename Node, typename T>
bool validateBST(Node* node, const T* minValue, const T* maxValue);
```

Reglas:

* Si `node == nullptr`, retorna `true`.
* Si existe `minValue`, entonces `node->data` debe ser mayor que `*minValue`.
* Si existe `maxValue`, entonces `node->data` debe ser menor que `*maxValue`.
* Valida recursivamente el subárbol izquierdo y derecho.
* No uses recorrido inorder como única validación.

Incluye comentarios en español:

```cpp
// Valida que cada nodo respete los limites heredados desde sus ancestros.
```

Entrega:

* Código fuente.
* Salida de la demostración.
* Explicación de por qué validar solo padre-hijo no es suficiente.

#### Ejercicio 2 - Contador de rotaciones AVL

Extiende una demostración o crea una nueva:

```bash
Semana7/demos/demo_avl_rotation_counter.cpp
```

El programa debe insertar varias secuencias y contar cuántas rotaciones aparecen en cada caso.

Secuencias mínimas:

```cpp
{30, 20, 10} // LL
{10, 20, 30} // RR
{30, 10, 20} // LR
{10, 30, 20} // RL
{10, 20, 30, 40, 50, 60, 70}
```

Salida esperada en formato similar:

```text
Caso LL
Rotaciones simples: 1
Rotaciones dobles: 0
Altura final: 1

Caso LR
Rotaciones simples: 0
Rotaciones dobles: 1
Altura final: 1
```

Entrega:

* Código fuente.
* Tabla con cada caso, secuencia, tipo de rotación y altura final.
* Explicación de por qué LR y RL no se resuelven con una sola rotación directa.

#### Ejercicio 3 - Verificador de balance AVL

Crea un archivo:

```bash
Semana7/demos/demo_validate_avl_balance.cpp
```

Implementa una función que verifique que todo nodo cumpla:

```text
|height(left) - height(right)| <= 1
```

Firma sugerida:

```cpp
template <typename Node>
bool validateAVLBalance(Node* node);
```

También implementa una función auxiliar:

```cpp
template <typename Node>
int computeHeight(Node* node);
```

Reglas:

* La altura de un árbol vacío debe ser `-1`.
* La altura de una hoja debe ser `0`.
* Debes validar todos los nodos, no solo la raíz.
* El programa debe imprimir si el árbol está balanceado o no.

Salida esperada:

```text
Validacion AVL despues de inserciones
Estado: balanceado
Altura calculada: 3
```

Entrega:

* Código fuente.
* Evidencia de ejecución.
* Explicación de la diferencia entre altura almacenada y altura calculada.

#### Ejercicio 4 - Comparación experimental BST vs AVL

Crea una demostración:

```bash
Semana7/demos/demo_compare_bst_avl_height.cpp
```

Inserta las mismas claves en un BST común y en un AVL.

Casos mínimos:

```cpp
std::vector<int> sortedKeys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::vector<int> mixedKeys = {5, 2, 8, 1, 3, 7, 9, 4, 6, 10};
```

El programa debe imprimir:

```text
Caso: claves ordenadas
Altura BST: 9
Altura AVL: 3

Caso: claves mezcladas
Altura BST: ...
Altura AVL: ...
```

Responde:

1. ¿Qué ocurre con el BST cuando las claves llegan ordenadas?
2. ¿Qué ocurre con AVL ante la misma entrada?
3. ¿Por qué ambas estructuras conservan el mismo inorder?
4. ¿Por qué la altura es la evidencia central en esta comparación?.

Entrega:

* Código fuente.
* Salida.
* Tabla comparativa.
* Interpretación.

#### Ejercicio 5 - Validador básico Red-Black Tree

Crea una demostración:

```bash
Semana7/demos/demo_validate_redblack_basic.cpp
```

Implementa validaciones básicas para Red-Black Tree:

1. La raíz debe ser negra.
2. No debe existir un nodo rojo con hijo rojo.
3. Todos los caminos desde un nodo hasta hojas nulas deben tener la misma altura negra.

Firmas sugeridas:

```cpp
template <typename Node>
bool validateNoRedRed(Node* node);

template <typename Node>
int computeBlackHeight(Node* node);

template <typename Node>
bool validateBlackHeight(Node* node);
```

Reglas:

* Considera las hojas nulas como negras.
* Si detectas violación, imprime un mensaje en español.
* No basta con imprimir el inorder.
* La validación debe revisar estructura y colores.

Salida esperada:

```text
Validacion Red-Black Tree
Raiz negra: correcto
Sin rojo-rojo: correcto
Altura negra uniforme: correcto
Estado final: valido
```

Entrega:

* Código fuente.
* Evidencia de ejecución.
* Explicación de por qué Red-Black Tree permite mayor flexibilidad que AVL.

#### Ejercicio 6 - Prueba pública adicional

Agrega una prueba pública en:

```bash
Semana7/pruebas_publicas/test_public_week7_extra.cpp
```

La prueba debe cubrir al menos:

1. Inserción ordenada en AVL.
2. Validación de inorder.
3. Validación de altura máxima razonable.
4. Inserción en Red-Black Tree.
5. Validación de búsqueda después de varias inserciones.

Ejemplo de intención:

```cpp
// Verifica que AVL no se degrade cuando recibe claves ordenadas.
```

No copies exactamente este pseudocódigo. Adáptalo a la interfaz real de la librería.

Entrega:

* Código de prueba.
* Comando usado para compilar.
* Comando usado para ejecutar.
* Resultado de `ctest`.
* Explicación de qué bug detectaría esta prueba.

#### Ejercicio 7 - Mini benchmark de búsqueda

Crea una demostración:

```bash
Semana7/demos/demo_search_benchmark_week7.cpp
```

Inserta `n` claves en:

1. BST común
2. AVL
3. Red-Black Tree

Usa al menos:

```cpp
n = 1000
n = 5000
n = 10000
```

Mide búsquedas exitosas y fallidas.

Reglas:

* Usa `std::chrono`.
* No imprimas cada búsqueda individual.
* Imprime tiempo total por estructura.
* Usa las mismas claves para todas las estructuras.
* Separa el caso ordenado del caso aleatorio.

Salida sugerida:

```text
n = 10000
Caso ordenado
BST search time: ...
AVL search time: ...
RedBlack search time: ...

Caso aleatorio
BST search time: ...
AVL search time: ...
RedBlack search time: ...
```

Entrega:

* Código fuente.
* Tabla de resultados.
* Interpretación.
* Conclusión sobre altura y costo de búsqueda.

#### Ejercicio 8 - Integración al CMake

Agrega tus demostraciones al `CMakeLists.txt` de Semana 7.

Debes poder compilar con:

```bash
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug -R semana7 --output-on-failure
```

Entrega:

* Fragmento modificado de `CMakeLists.txt`.
* Evidencia de compilación.
* Evidencia de pruebas.
* Explicación de por qué una demostración no necesariamente es una prueba automatizada.

#### Entrega mínima de codificación

Para considerar completo este bloque, debes entregar como mínimo:

1. Dos demostraciones nuevas.
2. Una prueba pública adicional.
3. Una tabla de resultados.
4. Una explicación de invariantes.
5. Evidencia de compilación.
6. Evidencia de ejecución.
7. Evidencia de `ctest`.

#### Pregunta final del bloque

Después de implementar los ejercicios, responde:

¿Por qué en estructuras balanceadas no basta con probar que el inorder está ordenado?

Tu respuesta debe mencionar:

* Propiedad BST.
* Altura.
* Rotaciones.
* Invariante AVL.
* Invariante Red-Black.
* Diferencia entre correctitud funcional y correctitud estructural.

#### Bloque 9 - Cierre comparativo

Responde esta pregunta final:

¿Qué cambia cuando pasamos de un BST común a estructuras balanceadas como AVL y Red-Black Tree?

La respuesta debe incluir obligatoriamente:

* Una afirmación sobre degeneración lineal del BST.
* Una afirmación sobre rotaciones y preservación del inorder.
* Una afirmación sobre balance por altura en AVL.
* Una afirmación sobre balance por colores en Red-Black Tree.
* Una afirmación sobre la diferencia entre balance estricto y balance flexible.
* Una afirmación sobre el costo esperado o garantizado de búsqueda, inserción y eliminación.
* Una afirmación sobre cómo esta semana continúa Semana 5 y Semana 6.
* Una afirmación sobre qué evidencia usarías para defender correctitud: pruebas, demostraciones, invariantes, trazados y complejidad.