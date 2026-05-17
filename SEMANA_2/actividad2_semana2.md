#### Bloque 1 - Núcleo conceptual de la semana

Revisen:
- `Semana2/README.md`
- **Lectura4-Deng**
- **Lectura5-Morin**
- `Semana2/include/ArrayStack.h`
- `Semana2/include/FastArrayStack.h`
- `Semana2/include/RootishArrayStack.h`
- `Semana2/include/DengVector.h`

Respondan:

1. Expliquen con sus palabras qué significa que un arreglo use **memoria contigua**.
Significa que todos sus elementos están almacenados uno junto al otro en la RAM, visto de otra forma:
- El primer elemento está en una **dirección base**.
- El elemento siguiente está en la **dirección base + tamaño del tipo**.
- El siguiente, en base + 2 * tamaño, y así sucesivamente. 

2. Expliquen por qué acceder a `A[i]` es una operación de costo `O(1)`.
Porque los arreglos utilizan memoria contigua, lo que permite calcular la dirección de memoria del elemento i de manera directa y constante. Específicamente, la dirección se obtiene como **dirección base + i * tamaño del elemento**

3. Expliquen la diferencia entre `size` y `capacity`.
- size: Representa el número de elementos actualmente almacenados en la estructura.
- capacity: Representa el espacio total reservado en memoria para el arreglo subyacente.
size es el espacio utilizado mientras que capacity es el espacion total.

4. Expliquen por qué un arreglo dinámico no puede crecer "en el mismo sitio" y necesita reservar un bloque nuevo al hacer `resize()`.
Porque el bloque adyacente en memoria podría estar ocupado por otros datos o procesos, impidiendo la expansión contigua.

5. Expliquen por qué duplicar capacidad permite defender costo amortizado `O(1)` para inserciones al final.
Porque la mayoría de las inserciones al final se hacen en un bloque ya reservado, con costo real O(1), solo algunas inserciones disparan resize(): cuando size == capacity.
Al duplicar la capacidad, cada resize() mueve todos los elementos actuales a un arreglo nuevo de tamaño el doble. Si la capacidad es (k), el siguiente resize() ocurre después de (k) inserciones exitosas sin copia, el costo total de esas (k) inserciones más el resize() es (O(k)) (copiar (k) elementos + (k) inserciones normales), dividiendo ese costo por las (k) inserciones, el costo promedio por operación es (O(1)).

6. Comparen `ArrayStack` y `DengVector`: ¿qué comparten y qué cambia en interfaz o intención didáctica?
Qué comparten:
Ambas estructuras usan memoria contigua (arreglo dinámico) con capacidad variable que se duplica cuando está llena, ofrecen acceso O(1) por índice, requieren desplazar elementos O(n) para inserciones intermedias, y logran costo amortizado O(1) para inserciones al final.

Qué cambia:
ArrayStack es pedagógico: solo tiene add(i), remove(i), get(i) y set(i).
DengVector es más completo y realista: ofrece operator[], insert por rango, remove por rango, búsqueda find(), encogimiento más agresivo (4n), copia profunda explícita, y función traverse() para recorridos funcionales.

7. Expliquen qué mejora `FastArrayStack` respecto a `ArrayStack`.
FastArrayStack mejora ArrayStack en eficiencia práctica al reemplazar bucles manuales con algoritmos de la biblioteca estándar de C++ std::copy (para copiar elementos al nuevo arreglo) y std::copy_backward (para desplazar elementos hacia la derecha), sin cambiar la complejidad asintótica (todavía O(1) amortizado para inserciones al final y O(n) para inserciones intermedias).

8. Expliquen cuál es la idea espacial central de `RootishArrayStack`.
En lugar de tener un solo bloque grande que se duplica cada vez que se llena (como en ArrayStack), el RootishArrayStack usa varios bloques más pequeños que van creciendo en tamaño.

9. Expliquen por qué `RootishArrayStack` usa bloques de tamaños `1, 2, 3, ...`.
Porque así logra una capacidad total 1 + 2 + 3 + ... + r = r(r+1)/2, que crece rápido pero con muy poco desperdicio.

10. Expliquen qué relación hay entre representación, costo temporal y desperdicio espacial en estas estructuras.
La representación determina cuánto espacio extra se necesita; ese espacio extra influye en cuándo y cuánto hay que copiar o reorganizar; y ese trabajo de reorganización es el que define el costo temporal amortizado.

#### Bloque 2 - Demostración y trazado guiado

Revisen:
- `Semana2/demos/demo_array_basico.cpp`
- `Semana2/demos/demo_arraystack.cpp`
- `Semana2/demos/demo_arraystack_explicado.cpp`
- `Semana2/demos/demo_fastarraystack.cpp`
- `Semana2/demos/demo_rootisharraystack.cpp`
- `Semana2/demos/demo_rootisharraystack_explicado.cpp`
- `Semana2/demos/demo_deng_vector.cpp`
- `Semana2/demos/demo_stl_vector_contraste.cpp`

Construyan una tabla con cuatro columnas:

- Archivo
- Salida u observable importante
- Idea estructural
- Argumento de costo o espacio

Luego respondan:

1. En `demo_array_basico.cpp`, ¿qué deja claro sobre arreglo, longitud y asignación?
El demo muestra que length es la “capacidad real” del arreglo y que la asignación puede mover la propiedad del bloque de memoria a otro arreglo.

2. En `demo_arraystack_explicado.cpp`, ¿qué operación muestra mejor el costo por desplazamientos?
Entonces, la mejor operación para ver el costo por desplazamientos es add(1, 15), porque el demo la usa para explicar directamente “desplazar a la derecha” y por qué eso encarece la operación.

3. En `demo_fastarraystack.cpp`, ¿qué cambia en la implementación aunque no cambie la complejidad asintótica?
En demo_fastarraystack.cpp lo que cambia es cómo se mueve la memoria internamente: FastArrayStack usa std::copy y std::copy_backward en lugar de hacer los desplazamientos con bucles for manuales.

4. En `demo_rootisharraystack_explicado.cpp`, ¿qué ejemplo explica mejor el mapeo de índice lógico a bloque y offset?
El ejemplo que mejor explica es cuando se imprimen las ubicaciones de los índices lógicos 0, 2 y 5 después de insertar seis elementos, porque muestra claramente cómo cada índice se traduce a un bloque y un offset específicos según el esquema de bloques de tamaños crecientes.

5. En `demo_deng_vector.cpp`, ¿qué observable permite defender el crecimiento de `capacity`?
El observable es que se imprime el valor de capacity() después de cada inserción, lo que permite ver cómo crece al aumentar el size.

6. En `demo_stl_vector_contraste.cpp`, ¿qué similitud conceptual observan con `DengVector`?
Ambos muestran un patrón de crecimiento de capacity al insertar elementos, lo que refleja la misma idea subyacente de reallocación geométrica para lograr tiempo amortizado constante.

7. ¿Qué demo sirve mejor para defender **amortización** y cuál sirve mejor para defender **uso de espacio**?
Para defender amortización, el demo demo_deng_vector.cpp sirve mejor porque muestra el crecimiento de la capacidad a lo largo de muchas inserciones y permite razonar sobre el costo amortizado.
Para defender uso de espacio, el mismo demo sirve mejor porque después de operaciones de inserción y eliminación se puede observar que la capacity puede ser mayor que el size, ilustrando el compromiso entre tiempo y espacio.

#### Bloque 3-Pruebas públicas, stress y correctitud

Revisen:
- `Semana2/pruebas_publicas/README.md`
- `Semana2/pruebas_publicas/test_public_week2.cpp`
- `Semana2/pruebas_internas/test_internal_week2.cpp`
- `Semana2/pruebas_internas/resize_stress_week2.cpp`

Respondan:

1. ¿Qué operaciones mínimas valida la prueba pública para `ArrayStack`?
Las operaciones mínimas son add al final, add en índice dado, get, remove, size.

2. ¿Qué operaciones mínimas valida la prueba pública para `FastArrayStack`?
Las operaciones mínimas son add al final (usando size), add en índice, remove en índice, get, size.

3. ¿Qué operaciones mínimas valida la prueba pública para `RootishArrayStack`?
Las operaciones mínimas son add en índice, get, set, remove, size.

4. ¿Qué sí demuestra una prueba pública sobre una estructura?
Demuestra corrección básica de inserción, lectura, actualización y eliminación.

5. ¿Qué no demuestra una prueba pública?
No demuestra rendimiento, costo amortizado, uso de espacio, invariantes ni comportamiento bajo carga extrema.

6. En `resize_stress_week2.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, reducción o estabilidad?
Intenta estresar el crecimiento (muchas inserciones) y la reducción (muchas eliminaciones) verificando que el tamaño y los valores sean correctos después de operaciones masivas.

7. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes y complejidad?
Porque las pruebas solo verifican casos específicos; no garantizan corrección para todos los posibles estados ni explican por qué la estructura funciona (invariantes) ni cuál es su complejidad asintótica.

#### Bloque 4-Vector como puente entre teoría y código

Revisen:
- `Semana2/include/DengVector.h`
- `Semana2/demos/demo_deng_vector.cpp`
- **Lectura4-Deng**

Respondan:

1. ¿Qué papel cumplen `_size`, `_capacity` y `_elem`?
_size cuenta los elementos almacenados, _capacity es el total de espacio asignado en el arreglo interno, y _elem es el puntero al arreglo dinámico que guarda los elementos.

2. ¿Cuándo debe ejecutarse `expand()`?
expand() debe ejecutarse cuando se va a insertar un elemento y el tamaño actual iguala la capacidad (es decir, no hay espacio libre); en insert se llama al inicio para asegurar espacio.

3. ¿Por qué `insert(r, e)` necesita desplazar elementos?
insert(r, e) necesita desplazar elementos para hacer espacio en la posición r y mantener el orden de los elementos existentes.

4. ¿Qué diferencia conceptual hay entre `remove(r)` y `remove(lo, hi)`?
remove(r) elimina un solo elemento en el índice r y devuelve su valor; remove(lo, hi) elimina el rango [lo, hi) y devuelve la cantidad de elementos borrados. El primero es un caso particular del segundo con hi = lo+1.

5. ¿Qué evidencia de copia profunda aparece en la demo?
En la demo, después de copia(v) y asignado = copia, se modifican copia y asignado mediante traverse y se muestra que el vector original v permanece sin cambios, indicando que cada copia tiene su propio arreglo (copia profunda).

6. ¿Por qué `traverse()` es una buena interfaz didáctica?
traverse() es una buena interfaz didáctica porque permite aplicar una operación a cada elemento sin exponer la representación interna, encapsulando la iteración y facilitando el estilo funcional de procesamiento (similar a map).

7. ¿Qué ventaja tiene implementar un vector propio antes de depender de `std::vector`?
Implementar un vector propio antes de usar std::vector ayuda a comprender la gestión dinámica de memoria, el redimensionamiento, la semántica de copia y el análisis amortizado, reforzando conceptos fundamentales y compromisos de diseño.

#### Bloque 5 - RootishArrayStack: espacio y mapeo

Revisen:
- `Semana2/include/RootishArrayStack.h`
- `Semana2/include/RootishArrayStackExplicado.h`
- `Semana2/demos/demo_rootisharraystack.cpp`
- `Semana2/demos/demo_rootisharraystack_explicado.cpp`
- **Lectura5-Morin**

Respondan:

1. ¿Cómo se distribuyen los elementos entre bloques?
Los elementos se almacenan en bloques donde el bloque b (índice 0‑based) tiene tamaño b+1. Se llenan secuencialmente: primero el bloque 0 (1 elemento), luego el bloque 1 (2 elementos), luego el bloque 2 (3 elementos), etc.

2. ¿Por qué con `r` bloques la capacidad total es `r(r+1)/2`?
La capacidad total de r bloques es la suma de sus tamaños:
($\sum_{k=0}^{r-1} (k+1) = \sum_{t=1}^{r} t = \frac{r(r+1)}{2}$).

3. ¿Qué problema resuelve `i2b(i)`?
i2b(i) resuelve el mapeo de un índice lógico i al número de bloque que lo contiene, invirtiendo la función triangular acumulativa mediante la fórmula ($b = \lceil(-3+\sqrt{9+8i})/2\rceil$).

4. ¿Qué información produce `locate(i)` en la versión explicada?
En la versión explicada, locate(i) devuelve una pareja (b, j) donde b es el bloque y j el offset dentro de ese bloque (es decir, j = i - b(b+1)/2), mostrando explícitamente la descomposición del índice.

5. ¿Qué se gana en espacio frente a `ArrayStack`?
Frente a ArrayStack, cuyo espacio desperdiciado puede ser Θ(n) (capacidad hasta 2·size), RootishArrayStack desperdicia solo O($\sqrt{n}$) porque el último bloque incompleto tiene tamaño $\approx \sqrt{2n}$. Así se reduce el overhead espacial de lineal a sublineal.

6. ¿Qué se conserva igual respecto a la interfaz?
Se conserva exactamente la misma interfaz pública (size, get, set, add, remove, clear) y la semántica de operaciones (tiempo amortizado constante por operación), por lo que cualquiera de estas estructuras puede intercambiarse sin cambiar el código que las usa.

7. ¿Qué parte les parece más difícil de defender oralmente: el mapeo, el análisis espacial o el costo amortizado de `grow/shrink`?
La parte más difícil de defender oralmente es el mapeo i2b(i), ya que implica pasar de un índice lineal i al bloque que lo contiene invirtiendo la suma triangular (b(b+1)/2); esa inversión lleva a la fórmula con raíz cuadrada que usa i2b y requiere explicar las “razones triangulares” (la relación entre i y los números triangulares) antes de llegar a la expresión final.

#### Bloque 6-Refuerzo de lectura

Revisen:
- **Lectura4-Deng**

Respondan brevemente:

1. ¿Qué aporta `operator[]` a la idea de vector?
operator[] brinda el acceso directo y natural por índice (como en un arreglo) sin romper la encapsulamiento del ADT, permitiendo usar la notación familiar mientras se mantiene la separación entre interfaz y implementación.

2. ¿Qué supone `find(e)` sobre igualdad entre elementos?
find(e) asume que existe una operación de igualdad definida para los elementos (se usa e == _elem[hi]), es decir, que los objetos son comparables con operator==.

3. ¿Qué muestra `traverse()` sobre procesamiento uniforme de toda la estructura?
traverse() muestra que se puede aplicar la misma operación a cada elemento de la estructura de forma uniforme, bien mediante punteros a función o functores, lo que refleja un procesamiento holístico y estilo de mapa sobre el vector.

4. ¿Por qué esta lectura sirve como refuerzo natural de `DengVector` aunque no sea el centro exclusivo de la semana?
La lectura refuerza naturalmente a DengVector porque detalla exactamente los conceptos que esa clase implementa: ADT con operaciones básicas, campos _elem, _size, _capacity, gestión dinámica mediante expand() y shrink(), política de copia profunda, y recorrido uniforme con traverse(). Todo ello corresponde directamente al código y al comportamiento observado en los demos de la semana.

#### Bloque 7 - Cierre comparativo

Respondan esta pregunta final:

**¿Qué cambia cuando pasamos de "usar un arreglo" a "diseñar una estructura dinámica basada en arreglo"?**
Al cambiar de un arreglo estático a uno dinámico:
- Representación: Necesitas 3 campos: _elem (datos), _size (elementos usados) y _capacity (espacio reservado).
- Correctitud: Mantener 0 ≤ _size ≤ _capacity, desplazar elementos correctamente al insertar/eliminar, y gestionar memoria (evitar fugas o dobles liberaciones).
- Costo amortizado: Aunque expandir cuesta O(n) por copiar todo, al duplicar capacidad el trabajo total de n inserciones es O(n), así que cada inserción cuesta O(1) en promedio.
- Uso de espacio: El vector clásico desperdicia hasta el doble de capacidad (O(n)). El RootishArrayStack mejora esto usando bloques de tamaños 1,2,3... desperdiciando solo O($\sqrt{n}$).

Comparación de pilas:
- ArrayStack / FastArrayStack: Un solo arreglo que se duplica. Sobre-espacio O(n). Costo amortizado O(1).
- RootishArrayStack: Bloques de tamaño creciente (1,2,3...). Sobre-espacio solo O(√n). Mismo costo O(1).
