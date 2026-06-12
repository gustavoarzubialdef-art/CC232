### PC3 - CC232 · Codeforces 702F: T-Shirts

**Estudiante:** ARZUBIALDE FIERRO GUSTAVO ANTHONY · Código 20230205H  
**Problema asignado:** [Codeforces 702F – T-Shirts](https://codeforces.com/problemset/problem/702/F)  

---

Esta carpeta contiene la solución a la PC3. El problema pide simular cuántas camisetas compra cada comprador si las recorre en orden de calidad descendente (precio ascendente en empates). La solución eficiente invierte los ciclos: itera sobre camisetas y actualiza en bloque a todos los compradores elegibles usando un Treap aumentado con marcas lazy.

---

#### Relación con la librería `cc232`

| Componente de la librería | Archivo | Cómo se usa en esta solución |
|---|---|---|
| `ods::Treap<T>::Node` | `Semana6/include/Treap.h` | `CustomerNode` hereda de él; reutiliza `priority`, `left`, `right`, `parent`, `isLeftChild()`, `isRightChild()` |
| `ods::BinaryHeap<T>` | `Semana5/include/BinaryHeap.h` | `sortedShirts()` usa su `heapify` + `trickleDown` para ordenar camisetas en O(n log n) |
| `ods::pqParent / pqLeftChild / pqRightChild` | `Semana6/include/PQ_ComplHeap_macro.h` | `benchmark/` los usa para mostrar índices del heap implícito |

Los tres headers están copiados en `include/cc232/` para que el proyecto compile sin depender de la ruta del repositorio raíz.

La extensión principal respecto a `ods::Treap` es la adición de `split`/`merge` no rotativos con propagación lazy. `ods::Treap` usa `bubbleUp`/`trickleDown` (Treap rotativo de Morin); esta solución necesita partir el árbol por valor de `money`, operación que el Treap rotativo no provee directamente.

---

#### Contenido principal

* `include/cc232/Treap.h`: copia de `Semana6/include/Treap.h` — base de `CustomerNode`
* `include/cc232/BinaryHeap.h`: copia de `Semana5/include/BinaryHeap.h` — usado en `sortedShirts()`
* `include/cc232/PQ_ComplHeap_macro.h`: copia de `Semana6/include/PQ_ComplHeap_macro.h` — índices del heap implícito
* `include/tshirts_solver.h`: API pública con `solveFast`, `solveNaive`, `verifyAgainstNaive` y `printOrderedTrace`
* `src/tshirts_solver.cpp`: `CustomerNode` (extiende `ods::Treap<int>::Node`), `CustomerTreap` con `splitLessThan`, `merge`, `insert`, `addLazy`, `collectAndInsert`, `push` y `checkInvariant`; también `sortedShirts` (usa `ods::BinaryHeap`), `solveFast`, `solveNaive` y `printOrderedTrace`
* `src/main.cpp`: entrada interactiva con prompts, salida compatible con Codeforces
* `tests/test_tshirts.cpp`: casos públicos, borde, comparación ingenua y prueba aleatoria
* `demos/demo_trace.cpp`: reto específico — estado del Treap después de cada camiseta
* `demos/demo_samples.cpp`: ejemplos oficiales del enunciado sin entrada interactiva
* `benchmark/benchmark_tshirts.cpp`: tiempos de `solveFast` vs `solveNaive` para distintos tamaños

---

#### Descripción de la solución

Las camisetas se ordenan por calidad descendente (precio ascendente en empates) usando `ods::BinaryHeap` con comparador personalizado. Ese orden es fijo y se procesa una sola vez.

`CustomerNode` extiende `ods::Treap<int>::Node` agregando `money`, `bought`, `lazyMoney` y `lazyBought`. El campo `key` heredado almacena el `id` del comprador para desempatar cuando dos compradores tienen el mismo dinero.

`CustomerTreap` mantiene el árbol ordenado por `(money, id)`. La operación central es `buyForEligible(price)`:

1. `splitLessThan(price)` separa quienes no pueden pagar.
2. `addLazy(-price, +1)` actualiza todo el segmento elegible en O(1).
3. Segundo `splitLessThan(price)` aísla quienes cruzaron la frontera al comprar.
4. `collectAndInsert` los reinserta en el segmento incapaz.
5. `merge` une ambos segmentos.

Las marcas lazy se propagan con `push` antes de cada descenso.

---

#### Invariante principal

El inorder del Treap está siempre ordenado por `(money, id)` — propiedad BST — y cada raíz tiene menor `priority` que sus hijos — propiedad heap. Esto es exactamente `ods::Treap::isTreap()`. `checkInvariant()` verifica ambas propiedades usando la misma lógica que `isBST()` e `isHeapByPriority()` de la librería. `assertInvariantIfSmall()` lo llama automáticamente cuando `k ≤ 256`.

---

#### Complejidad

* **Por operación:** `split`, `merge` e `insert` en `O(log k)` esperado; `addLazy` en `O(1)` por subárbol.
* **Total:** `O((n + k) log k)` esperado/amortizado. Las reinserciones de `collectAndInsert` se amortizan porque cada nodo reinsertado cruzó la frontera `[c, 2c) → [0, c)`.
* **Espacial:** `O(k + n)`.

---

#### Pruebas incluidas

* `sampleOne` y `sampleTwo`: ejemplos públicos del enunciado
* `minimalCase`: una camiseta, presupuesto justo debajo y justo igual al precio
* `tieByQualityUsesCheaperFirst`: empates de calidad ordenados por menor precio
* `boundaryWithCrossingCustomers`: compradores que caen por debajo de la frontera al comprar
* `explicitNaiveComparison`: comparación directa `solveFast` vs `solveNaive`
* `smallRandomAgainstNaive`: 200 casos aleatorios pequeños contra fuerza bruta

---

#### Retos elegidos

* **Reto transversal 1 – comparación contra versión ingenua:** `verifyAgainstNaive` y `explicitNaiveComparison`.
* **Reto transversal 2 – prueba aleatoria pequeña:** `smallRandomAgainstNaive` con 200 instancias.
* **Reto específico del problema:** `demo_trace` — estado inorder del Treap después de cada camiseta.

---

#### Organización de la carpeta

* `include/cc232/`: headers de la librería `cc232` usados por esta solución
* `demos/`: traza interna del Treap y ejemplos oficiales
* `benchmark/`: comparación de tiempos `solveFast` vs `solveNaive`
* `docs/bitacora.md`: avance diario del desarrollo
* `docs/respuestas_obligatorias.md`: 20 preguntas comunes y 3 preguntas específicas
* `resultados/casos_borde.txt`, `ejecucion_pc3.txt`, `tests_pc3.txt`: evidencia textual

---

### MSYS2 UCRT64

#### 1. Configurar y compilar

```bash
cd EVALUACIONES/PCs/ARZUBIALDE_GUSTAVO_pc3
cmake -S . -B build
cmake --build build
```

#### 2. Ejecutar todo de una vez

```bash
cmake -S . -B build && cmake --build build && \
./build/demo_samples.exe && \
./build/demo_trace.exe && \
ctest --test-dir build --output-on-failure
```

#### 3. Ejecutar cada binario por separado

##### Ejemplos oficiales sin entrada

```bash
./build/demo_samples.exe
```

##### Demo de traza interna del Treap

```bash
./build/demo_trace.exe
```

##### Benchmark

```bash
./build/benchmark_tshirts.exe
```

Muestra tiempos de `solveFast` vs `solveNaive` para n y k crecientes, e índices del heap implícito usando `ods::pqParent`/`pqLeftChild`/`pqRightChild` de Semana6.

##### Binario principal (entrada interactiva)

```bash
./build/tshirts.exe
```

##### Pruebas unitarias

```bash
./build/test_tshirts.exe
```

##### Todas las pruebas con ctest

```bash
ctest --test-dir build --output-on-failure
```

---

### Targets principales

| Target | Descripción |
|---|---|
| `tshirts` | Binario principal, entrada interactiva compatible con Codeforces |
| `demo_samples` | Ejemplos oficiales sin entrada interactiva |
| `demo_trace` | Traza interna del Treap por camiseta |
| `benchmark_tshirts` | Tiempos `solveFast` vs `solveNaive` |
| `test_tshirts` | Pruebas unitarias, borde, comparación y aleatorios |

---

#### Limpieza del repositorio

```bash
git status
git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles)"
cat .gitignore
```

---

#### Declaración de autoría

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo durante la grabación. También declaro que el repositorio entregado corresponde al trabajo mostrado en el video y que no contiene builds, ejecutables ni archivos generados usados para aparentar funcionamiento.
