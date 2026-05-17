#### Bloque 1 - Núcleo conceptual de la semana

Revisa:

- `Semana3/README.md`
- `Semana3/lecturas/Lectura6-Deng.md`
- `Semana3/lecturas/Lectura7-Morin.md`
- `Semana3/include/SLList.h`
- `Semana3/include/DLList.h`
- `Semana3/include/SEList.h`
- `Semana3/include/DengList.h`
- `Semana3/include/MorinDengBridge.h`

Responde:

1. Explica con tus palabras qué cambia cuando una estructura pasa de almacenamiento contiguo a almacenamiento dinámico.
La memoria ya no es un bloque único sino nodos dispersos conectados por punteros.

2. Explica la diferencia entre acceso por rango y acceso por posición o enlace.
- El acceso por rango se refiere a obtener el elemento que tiene exactamente r predecesores, sin asumir cómo están dispuestos físicamente los datos.
- El acceso por posición implica que los elementos están almacenados en direcciones contiguas y que la dirección del elemento i se calcula como base + i·tamaño.
- El acceso por enlace significa llegar al elemento siguiendo punteros de nodo en nodo, sin usar ninguna fórmula aritmética sobre índices.

3. Explica por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice.
En una lista enlazada, insertar o eliminar un nodo solo requiere cambiar los punteros de los nodos vecinos; si ya se tiene una referencia al nodo de trabajo, la operación es O(1). En cambio, para acceder por índice hay que comenzar en la cabeza y seguir i enlaces, lo que cuesta O(i) en el peor caso y O(n) en promedio.

4. Explica por qué `SLList` implementa bien operaciones de `Stack` y `Queue`.
SLList mantiene punteros head y tail.
- Stack: push inserta en la cabeza (o en la cola si se invierte) y pop elimina de la misma cabeza; ambos son solo unas pocas asignaciones de punteros → O(1).
- Queue: add (o enqueue) inserta en la cola usando tail y remove (o dequeue) elimina de la cabeza usando head; nuevamente, solo se actualizan uno o dos punteros → O(1).

5. Explica por qué `SLList` no implementa naturalmente todas las operaciones de un `Deque` con el mismo costo.
Un Deque necesita inserción y eliminación eficientes en ambos extremos. En SLList podemos agregar en la cabeza (push) y en la cola (add) en O(1), y eliminar de la cabeza (pop) en O(1), pero eliminar de la cola requiere recorrer la lista hasta el predecessor de tail (o mantener un puntero extra), lo que es O(n). Por tanto, no se obtienen los cuatro extremos con el mismo costo.

6. Explica qué aporta el nodo centinela `dummy` en `DLList`.
El nodo centinela dummy se coloca de modo que la lista nunca esté realmente vacía: head y tail siempre apuntan a nodos válidos (el centinela o un nodo real). Esto elimina los casos especiales de lista vacía o de un solo elemento en las operaciones de inserción, eliminación, acceso y actualización, permitiendo que el mismo código de recorrido y actualización de punteros funcione sin verificaciones nulas adicionales.

7. Explica por qué `DLList` permite justificar `get(i)`, `set(i,x)`, `add(i,x)` y `remove(i)` con costo `O(1 + min(i, n-i))`.
Para acceder al índice i se puede partir de la cabeza y avanzar i pasos, o partir de la cola y retroceder n‑1‑i steps. El costo es por tanto el mínimo de esas dos distancias más una constante para el acceso al nodo resultante. El mismo razonamiento vale para set, add y remove.

8. Explica cuál es la idea espacial central de `SEList`.
La idea central de SEList es almacenar los elementos en bloques enlazados entre sí, en lugar de un solo nodo por elemento. Cada bloque contiene varios elementos contiguos, lo que mejora la localidad de referencia y reduce el overhead de punteros, mientras que la lista de bloques conserva la flexibilidad de una estructura enlazada para insertar y eliminar bloques cuando sea necesario.

9. Explica por qué `SEList` reutiliza una `BDeque` basada en `ArrayDeque`.
SEList reutiliza una BDeque basada en ArrayDeque porque dicha estructura ya proporciona operaciones de inserción y eliminación en ambos extremos en tiempo amortizado O(1) y acceso directo a cualquier posición dentro del bloque. Al construir la lista de bloques sobre ese deque, SEList hereda esas propiedades eficientes dentro de cada bloque y solo necesita manejar la conexión entre bloques, lo que simplifica mucho la implementación.

10. Explica qué papel cumple `DengList` dentro de esta semana y por qué no reemplaza a las estructuras de Morin.
DengList es una lista simplemente enlazada que se presenta como ejemplo de ADT secuencial centrado en operaciones como insert, remove, find, traverse y acceso por posición. El objetivo de la semana es ofrecer una contraste con las listas de Morin y para ilustrar conceptos como invariantes, copia profunda y recorrido uniforme. No reemplaza a las estructuras de Morin porque la semana enfatiza la comparación entre representaciones contiguas y enlazadas, y las estructuras de Morin brindan precisamente esas variantes que DengList no cubre.



#### Bloque 2 - Demostración y trazado guiado

Revisa:

- `Semana3/demos/demo_sllist.cpp`
- `Semana3/demos/demo_dllist.cpp`
- `Semana3/demos/demo_selist.cpp`
- `Semana3/demos/demo_deng_list.cpp`
- `Semana3/demos/demo_morin_deng_bridge.cpp`
- `Semana3/demos/demo_capitulo3_panorama.cpp`
- `Semana3/demos/demo_min_structures.cpp`
- `Semana3/demos/demo_xor_list.cpp`
- `Semana3/demos/demo_linked_adapters.cpp`
- `Semana3/demos/demo_contiguous_vs_linked.cpp`

Construye una tabla con cuatro columnas:

- Archivo
- Salida u observable importante
- Idea estructural
- Argumento de costo, espacio o diseño

Luego responde:

1. En `demo_sllist.cpp`, ¿qué secuencia deja más clara la coexistencia de comportamiento tipo pila y tipo cola dentro de `SLList`?
Pila: push(5) inserta al inicio, pop() remueve del inicio. La lista actúa como LIFO (Last In, First Out).
Cola: add(10) y add(20) insertan al final, remove() remueve del inicio. La lista actúa como FIFO (First In, First Out).
Coexistencia: Ambas operaciones comparten el mismo extremo (el frente) para acceso/remoción, pero usan extremos opuestos para inserción.
Esto demuestra cómo SLList puede simular ambas estructuras.

2. En `demo_dllist.cpp`, ¿qué operación muestra mejor la inserción en una posición intermedia?
add(1, 20) inserta el valor 20 en la posición índice 1, desplazando el elemento existente (30) hacia la derecha.
La lista queda como [10, 20, 30], demostrando cómo DLList permite inserciones eficientes en posiciones arbitrarias sin necesidad de desplazar todos los elementos

3. En `demo_selist.cpp`, ¿qué observable permite defender que la lista mantiene orden lógico aunque internamente trabaje por bloques?
La impresión de los elementos en orden creciente (0 10 20 30 40 50 60 70 80 90) después de haber insertado secuencialmente en cada índice demuestra que, pese a que los datos están almacenados en bloques de tamaño fijo enlazados, el orden lógico de la secuencia se preserva exactamente como se esperaría de una lista lineal.

4. En `demo_deng_list.cpp`, ¿qué evidencia muestra que la lista reforzada por Deng ofrece operaciones más cercanas a un ADT de lista completo?
Además de las operaciones básicas (push_back, push_front, front, back, size), la lista permite sort() y luego imprimir su contenido mediante to_vector(), mostrando que soporta un conjunto completo de operaciones típicas de una lista (inserción en ambos extremos, consulta de extremos, tamaño, ordenación y conversión a otro contenedor) sin necesidad de cambiar su representación interna.

5. En `demo_morin_deng_bridge.cpp`, ¿qué parte de la salida permite justificar que se reutilizan algoritmos sin reescribir la estructura base?
La línea DLList reforzada con Deng: 1 2 3 4 indica que los resultados de stable_sort_with_deng y dedup_with_deng se aplicaron directamente sobre una DLList de Morin; el hecho de que la lista original no se modificó en su estructura y que los algoritmos de Deng produzcan el orden esperado muestra que se está reutilizando el código de los algoritmos sin tener que reimplementar ni copiar la lista.

6. En `demo_min_structures.cpp`, ¿qué diferencia conceptual observas entre almacenar valores y almacenar información adicional para responder `min()`?
Las estructuras normales (SLList, DLList, etc.) almacenan únicamente los valores de los elementos. Las variantes mínimas (MinStack, MinQueue, MinDeque) guardan, junto con cada nodo o en una estructura auxiliar, el mínimo acumulado hasta ese punto (o una pila de mínimos), de modo que la operación min() pueda devolverse en O(1) sin recorrer toda la estructura; esto implica un overhead espacial adicional pero reduce el costo temporal de consultas de mínimo.

7. En `demo_linked_adapters.cpp`, ¿qué adaptador representa mejor la idea de reutilizar una estructura existente para ofrecer una interfaz nueva?
El adaptador que mejor representa es LinkedDeque porque toma una DLList (que ya permite inserción y eliminación eficientes en ambos extremos) y le proporciona la interfaz de deque (addFirst, addLast, removeFirst, removeLast, front, back) mediante simples delegaciones, mostrando claramente cómo se puede reutilizar una estructura existente para ofrecer una nueva interfaz sin reescribir su lógica central.

8. En `demo_contiguous_vs_linked.cpp`, ¿qué contraste se observa entre acceso por índice, inserción local y localidad de memoria?
El acceso por índice es O(1) y muy rápido en la práctica en ArrayDeque gracias a la contigüidad de memoria, mientras que en DLList es O(min(i, n-i)) y requiere recorrer enlaces. Las inserciones/eliminaciones en los extremos son O(1) en ambas, pero en el medio ArrayDeque necesita desplazamiento de elementos (O(n)) mientras que DLList solo cambia punteros (O(1) tras la localización). En cuanto a localidad de memoria, ArrayDeque aprovecha mejor la caché porque los elementos están almacenados contiguamente; DLList tiene peor localidad debido a la dispersión de nodos en memoria. Este contraste muestra el compromiso entre acceso rápido por índice y flexibilidad en modificaciones locales.

#### Bloque 3 - Pruebas públicas, stress y correctitud

Revisa:

- `Semana3/pruebas_publicas/README.md`
- `Semana3/pruebas_publicas/test_public_week3.cpp`
- `Semana3/pruebas_publicas/test_public_deng_bridge.cpp`
- `Semana3/pruebas_publicas/test_public_extras.cpp`
- `Semana3/pruebas_publicas/test_public_linked_adapters.cpp`
- `Semana3/pruebas_publicas/test_public_contiguous_vs_linked.cpp`
- `Semana3/pruebas_internas/test_internal_week3.cpp`
- `Semana3/pruebas_internas/test_internal_deng_algorithms.cpp`
- `Semana3/pruebas_internas/test_internal_extras.cpp`
- `Semana3/pruebas_internas/stress_selist_week3.cpp`

Responde:

1. ¿Qué operaciones mínimas valida la prueba pública para `SLList`?
- add(int i, const T& x): Inserción en posiciones específicas (índices 0, 1, 1).
- get(int i): Acceso por índice para verificar elementos.
- remove(int i): Eliminación por índice.
- size(): Consulta del tamaño de la lista.

2. ¿Qué operaciones mínimas valida la prueba pública para `DLList`?
La operaciones mínimas son add (en índice dado), get, remove (en índice), size.

3. ¿Qué operaciones mínimas valida la prueba pública para `SEList`?
La operaciones mínimas son add (en índice), get, set, remove, size.

4. ¿Qué operaciones nuevas quedan cubiertas por `test_public_extras.cpp`?
Las nuevas operaciones son to_vector, secondLast, reverse, checkSize; rotate, isPalindrome; min (MinStack/MinQueue/MinDeque); front, back, removeLast (MinDeque/MinQueue); reverse, to_vector.

5. ¿Qué valida específicamente `test_public_linked_adapters.cpp` sobre `LinkedStack`, `LinkedQueue` y `LinkedDeque`?
Valida que LinkedStack implementa push, pop, top, size, empty; LinkedQueue implementa add, remove, front, size, empty; LinkedDeque implementa addFirst, addLast, removeFirst, removeLast, front, back, size, empty.

6. ¿Qué demuestra `test_public_deng_bridge.cpp` sobre integración y reutilización?
Muestra que algoritmos de Deng pueden aplicarse directamente sobre DLList y SEList de Morin sin modificar sus estructuras, probando correctitud mediante to_vector.

7. En `stress_selist_week3.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, borrado y mantenimiento del tamaño lógico?
Intenta estresar crecimiento masivo de elementos (500 inserciones), eliminación repetida desde el frente (250 remove(0)), y nuevas inserciones en posiciones iniciales después de reducciones, verificando que el tamaño lógico termine en 350.

8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?
Demuestra corrección básica de inserción, eliminación, acceso y tamaño bajo secuencias simples de operaciones.

9. ¿Qué no demuestra una prueba pública por sí sola?
No demuestra invariantes de punteros, uso de espacio, costo amortizado, comportamiento bajo todos los casos frontera ni ausencia de fugas de memoria.

10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, punteros y complejidad?
Porque las pruebas solo verifican casos específicos; no garantizan que los invariantes (punteros, cabeza/cola) se mantengan en todas las ejecuciones, no explican por qué la complejidad es O(1) u O(n) ni cubren todas las posibles secuencias de operaciones.

#### Bloque 4 - SLList, DLList y SEList: lectura cercana del código

Revisa:

- `Semana3/include/SLList.h`
- `Semana3/include/DLList.h`
- `Semana3/include/SEList.h`
- `Semana3/lecturas/Lectura7-Morin.md`
- `Semana3/lecturas/Lectura6-Deng.md`

Responde:

1. En `SLList`, ¿qué papel cumplen `head`, `tail` y `n`?
head apunta al primer nodo, tail al último nodo (o nullptr si la lista está vacía), y n cuenta el número de nodos reales.

2. En `SLList::push`, `pop`, `add` y `remove`, ¿qué punteros cambian exactamente?
En push: se crea u; u->next = head; head = u; si n==0 entonces tail = u. En pop/remove(): se guarda u = head; head = head->next; si tras eliminar n==0 entonces tail = nullptr; se elimina u. En add(x) (al final): se crea u; si n==0 entonces head = tail = u; sino tail->next = u; tail = u. En add(i,x) con 0<i<n: se busca prev = nodeAt(i-1); se crea u; u->next = prev->next; prev->next = u. En todos los casos se incrementa o decrementa n y solo se modifican los punteros next de los nodos afectados y posiblemente head/tail.

3. Explica cómo funciona `secondLast()` y por qué no puede resolverse directamente con solo mirar `tail`.
secondLast() recorre desde head hasta encontrar el nodo cuyo next es tail; no basta con mirar tail porque en una lista simple sólo se tiene enlace hacia adelante, por lo que desde tail no se puede llegar al predecesor sin recorrer toda la lista.

4. Explica paso a paso cómo funciona `reverse()` y por qué no necesita estructura auxiliar.
reverse() invierte los enlaces next de cada nodo usando tres punteros (prev, curr, next). Inicialmente prev=nullptr, curr=head, y tail se guarda como antiguo head. En cada iteración se guarda next=curr->next, se invierte curr->next=prev, se avanza prev=curr, curr=next. Al terminar, head=prev (último nodo procesado) y la lista queda invertida sin usar memoria adicional más allá de unas pocas variables locales.

5. Explica qué verifica `checkSize()` y por qué esta función ayuda a defender correctitud.
checkSize() recorre la lista contando nodos y verifica que la cuenta coincida con n, que head y tail sean nullptr cuando n==0, y que cuando n>0 head no sea nullptr y tail sea efectivamente el último nodo alcanzado. Así comprueba que los punteros internos y el contador sean consistentes, lo que ayuda a detectar errores de inserción/eliminación que rompan los invariantes.

6. En `DLList`, explica por qué `getNode(i)` puede empezar desde el inicio o desde el final.
En DLList (con nodo centinela dummy), getNode(i) puede partir del principio (dummy.next) y avanzar i pasos, o partir del final (dummy.prev) y retroceder n-1-i pasos. Elegir el camino más corto da O(1+min(i,n-i)). Esto es posible porque cada nodo tiene punteros tanto al sucesor como al predecesor.

7. En `DLList::addBefore`, ¿qué enlaces se actualizan y por qué el nodo centinela elimina casos borde?
En addBefore(w) se crea un nodo u; se enlaza u->prev = w->prev, u->next = w; luego se actualizan los vecinos: w->prev->next = u y w->prev = w. El nodo centinela asegura que w->prev y w->next siempre sean nodos válidos (incluso cuando se inserta al inicio o al final), eliminando la necesidad de tratar casos de lista vacía o de actualizar head/tail explícitamente.

8. Explica cómo funciona `rotate(r)` sin mover los datos elemento por elemento.
rotate(r) simplemente cambia cuál nodo se considera el inicio lógico: avanza r pasos desde dummy.next (o retrocede según el signo) y vuelve a enlazar el último nodo con el primero. No se mueve ningún dato; sólo se reordena la referencia al nodo que actúa como cabeza, aprovechando la naturaleza circular implícita de la lista con centinela.

9. Explica cómo `isPalindrome()` aprovecha la naturaleza doblemente enlazada de la estructura.
isPalindrome() coloca dos punteros, uno al inicio (dummy.next) y otro al final (dummy.prev). En cada paso compara los valores que apuntan; si son distintos retorna falso. Luego avanza el primero hacia adelante (= u->next) y el segundo hacia atrás (= v->prev). Gracias a los enlaces dobles, ambos pueden moverse en O(1) por paso y se encuentran en el medio, verificando el palíndromo sin necesidad de una estructura auxiliar.

10. En `SEList`, explica qué representa `Location`.
Location es un par (u, j) donde u es puntero al nodo de bloque (BDeque) que contiene el elemento de índice global i, y j es el offset dentro de ese bloque (posición del elemento en el arreglo del bloque). Permite traducir un índice lineal a la estructura de bloques sin recorrer toda la lista.

11. Explica qué hacen `spread()` y `gather()` y en qué situaciones aparecen.
spread(u) toma un bloque u que está demasiado lleno (tamaño b+1) y redistribuye su exceso a los b bloques siguientes, moviendo un elemento de cada bloque siguiente al anterior, de modo que todos queden con tamaño ≤ b. Se llama cuando una inserción provocaría un bloque de tamaño b+2. gather(u) hace lo contrario: toma una secuencia de b bloques cuyo tamaño total es bajo (cada uno tiene b-1 o menos) y recolecta elementos de los bloques siguientes para llenarlos, eliminando el último bloque si queda vacío. Se llama cuando una eliminación deja bloques muy poco llenos, para mantener el uso de espacio eficiente.

12. Explica cómo el tamaño de bloque `b` afecta el trade-off entre acceso, actualización y uso de espacio.
El tamaño de bloque b determina cuántos elementos hay por nodo de bloque. Un b grande reduce el número de nodos (menos punteros, mejor localidad) pero aumenta el costo de desplazamientos dentro de un bloque al insertar/eliminar (O(b)). Un b pequeño hace que la estructura se comporte más como una lista tradicional (más punteros, peor locality) pero reduce el costo de ajustes dentro de un bloque. El acceso por índice requiere encontrar el bloque correcto (O(number of blocks) = O(n/b)) y luego el offset dentro del bloque (O(1)). Así, el trade‑off se equilibra eligiendo b alrededor de $\sqrt{n}$ para obtener O($\sqrt{n}$) en ambas dimensiones, o fijando una constante (como 3) para obtener operaciones amortizadas O(1) con un overhead razonable.

#### Bloque 5 - Adaptadores y estructuras derivadas

Revisa:

- `Semana3/include/LinkedStack.h`
- `Semana3/include/LinkedQueue.h`
- `Semana3/include/LinkedDeque.h`
- `Semana3/include/MinStack.h`
- `Semana3/include/MinQueue.h`
- `Semana3/include/MinDeque.h`
- `Semana3/demos/demo_linked_adapters.cpp`
- `Semana3/demos/demo_min_structures.cpp`

Responde:

1. ¿Cómo reutiliza `LinkedStack` a `SLList`?
LinkedStack contiene un miembro SLList<T> list; y delega cada operación (push, pop, top, size, empty, clear) directamente al método correspondiente de list. No duplica lógica; simplemente expone la pila mediante la lista.

2. ¿Cómo reutiliza `LinkedQueue` a `SLList`?
LinkedQueue también contiene un SLList<T> list;. Usa list.add(x) para encolar (agrega en la cola), list.remove() para desencolar (quita de la cabeza) y list.peek() para obtener el frente. Así reutiliza la lista como una cola FIFO.

3. ¿Por qué `LinkedDeque` se construye naturalmente sobre `DLList` y no sobre `SLList`?
LinkedDeque se construye sobre DLList porque una lista doblemente enlazada permite inserción y eliminación en ambos extremos en O(1) mediante add(0,x), add(size(),x), remove(0) y remove(size()-1). Una SLList solo garantiza O(1) en la cabeza (push/pop) y O(1) al final para add pero no para remove del final (requiere recorrido). Para ofrecer un deque con las cuatro operaciones en O(1) se necesita la simetría de DLList.

4. En `MinStack`, ¿por qué cada entrada guarda el valor y el mínimo acumulado?
En MinStack cada nodo almacena un par (valor, mínimo_hasta_ese_valor). Cuando se apila un nuevo elemento, el nuevo mínimo es min(valor, mínimo_anterior). Así, el mínimo de toda la pila siempre está disponible en el elemento superior, permitiendo min() en O(1) sin estructura extra ni recorrido.

5. En `MinQueue`, ¿por qué usar dos pilas permite mantener semántica FIFO y consulta de mínimo?
MinQueue implementa una cola con dos pilas (in y out). Encolar apila en in; desencolar descarga de out (trasladando todo de in a out cuando out está vacío). Cada pila mantiene su propio mínimo (como en MinStack). El mínimo de la cola es el menor de los mínimos de las dos pilas. Esta disposición preserva el orden FIFO porque los elementos salen en el mismo orden que entraron, y la consulta de mínimo sigue siendo amortizada O(1) (el costo de trasladar se amortiza).

6. En `MinDeque`, ¿qué problema resuelve el rebalanceo entre `front_` y `back_`?
MinDeque mantiene dos pilas (front_ y back_) que representan la mitad delantera y trasera del deque, cada una con su propio mínimo. Para garantir que ninguna de ellas se desequilibre demasiado, después de ciertas operaciones se rebalancea: se mueven elementos de una pila a la otra hasta que sus tamaños difieran como máximo en uno. Esto garantiza que las operaciones de inserción y eliminación en cualquier extremo sigan siendo amortizadas O(1) y que el mínimo global sea simplemente min(front_.min(), back_.min()).

7. Compara "implementar una estructura" y "adaptar una estructura existente" usando ejemplos de este bloque.
Implementar una estructura significa escribir la lógica de almacenamiento, punteros, redimensionamiento, etc., desde cero (ej.: SLList, DLList, SEList, ArrayDeque). Adaptar una estructura existente consiste en tomar una ya implementada y envolverla con una nueva interfaz sin cambiar su funcionamiento interno (ej.: LinkedStack adapta SLList, LinkedQueue adapta SLList, LinkedDeque adapta DLList, MinStack/MinQueue/MinDeque adaptan pilas para agregar la consulta de mínimo). La ventaja del adaptador es reutilizar código probado y evitar duplicación.

8. ¿Qué operaciones puedes defender como constantes y cuáles debes defender como amortizadas?
Operaciones en tiempo constante O(1):
- SLList: push, pop, peek, add al final, remove de la cabeza.
- DLList con centinela: add/remove en extremos, get/set en extremos.
- Adaptadores (Stack, Queue, Deque): todas las operaciones básicas (push/pop/top, add/remove/front/back).

Operaciones amortizadas O(1):
- Expansión/contracción en arreglos dinámicos (ArrayDeque, std::vector).
- Transferencias/rebalanceo en MinQueue y MinDeque.

#### Bloque 6 - Deng como refuerzo algorítmico y puente de integración

Revisa:

- `Semana3/include/CleanList.h`
- `Semana3/include/DengList.h`
- `Semana3/include/MorinDengBridge.h`
- `Semana3/demos/demo_deng_list.cpp`
- `Semana3/demos/demo_morin_deng_bridge.cpp`
- `Semana3/pruebas_publicas/test_public_deng_bridge.cpp`
- `Semana3/pruebas_internas/test_internal_deng_algorithms.cpp`
- `Semana3/lecturas/Lectura6-Deng.md`

Responde:

1. ¿Qué operaciones del ADT de lista aparecen reforzadas en `DengList`?
DengList refuerza las operaciones del ADT de lista: inserción en ambos extremos (push_front, push_back), inserción por índice (add(index)), acceso y consulta (front, back, get), actualización (set), eliminación por índice (remove(index)), búsqueda (contains, find_index), recorrido (to_vector), ordenamiento estable (sort), eliminación de duplicados (dedup, uniquify), inversión (reverse), consulta de tamaño (size), vacío (empty) y limpieza (clear).

2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar el resto de estructuras de Semana 3?
Encapsular una lista más rica (DengList) permite ofrecer operaciones avanzadas (orden, deduplicación, inversión) sin modificar las estructuras existentes de la Semana 3 (SLList, DLList, SEList). Así se conserva su especialización (pila, cola, deque, listas por bloques) y se gana flexibilidad al convertir a DengList solo cuando se necesitan esas operaciones, promoviendo reutilización y separación de intereses.

3. Explica qué hacen `to_deng` y `assign_from_deng`.
to_deng(src) crea un nuevo DengList<T>, recorre la lista fuente (DLList o SEList) elemento a elemento con get(i) y lo inserta con push_back, devolviendo una copia en formato Deng. assign_from_deng(dst, src) limpia la lista destino, copia todos los elementos de src (usando src.to_vector()) y los inserta en dst mediante add (o add(index) para SEList). En conjunto permiten convertir entre representaciones sin exponer los detalles internos.

4. Explica por qué `stable_sort_with_deng` no obliga a reimplementar ordenamiento dentro de `DLList` o `SEList`.
stable_sort_with_deng no requiere reimplementar el ordenamiento dentro de DLList o SEList porque delega el trabajo a DengList: primero convierte la lista origen a un DengList (copiando sus elementos), llama a DengList::sort() (que usa std::stable_sort sobre un vector) y luego copia el resultado de vuelta a la lista original mediante assign_from_deng. El algoritmo de orden se escribe una sola vez; las listas de Morin solo deben proporcionar acceso de lectura/escritura por índice, lo que ya tienen.

5. Explica qué hace `dedup_with_deng` y qué relación guarda con `deduplicate()` o `uniquify()` de la teoría.
dedup_with_deng convierte la lista origen a DengList, ejecuta su método dedup() (que elimina todas las ocurrencias duplicadas de un valor, dejando solo la primera aparición), copia la lista deduplicada de vuelta y devuelve el número de elementos eliminados. En DengList, dedup() corresponde a la operación de deduplicación global de la teoría (no a uniquify, que solo elimina duplicados adyacentes). Por tanto dedup_with_deng implementa la deduplicación completa sobre cualquier lista que admita la conversión.

6. Explica por qué `reverse_with_deng` es un ejemplo de reutilización de algoritmos sobre una interfaz común.
reverse_with_deng es un caso de reutilización de algoritmo porque la lógica de inversión está definida una única vez en DengList (o CleanList): convierte la lista origen a DengList, invierte su vector interno con std::reverse y escribe el resultado de vuelta. Cualquier estructura que soporte to_deng y assign_from_deng (DLList, SEList, etc.) puede usar esa misma función de inversa sin necesidad de reescribirla para cada una.

7. ¿Qué costo adicional introduce la conversión entre estructuras y cuándo vale la pena aceptarlo?
La conversión introduce un costo adicional de O(n) tiempo y O(n) espacio extra (para copiar los elementos a un vector interno o al DengList). Vale la pena aceptarlo cuando se necesita una operación que la lista origen no soporta eficientemente (ordenamiento, deduplicación global, inversión) y se está dispuesto a pagar ese overhead lineal para reutilizar una implementación probada, especialmente si la operación es poco frecuente o el tamaño de la lista es moderado. En esos casos, el beneficio de corrección y simplicidad supera el costo de la copia.

#### Bloque 7 - Comparación enlazado vs contiguo, variantes y evidencia experimental

Revisa:

- `Semana3/include/ArrayDeque.h`
- `Semana3/include/XorList.h`
- `Semana3/demos/demo_contiguous_vs_linked.cpp`
- `Semana3/demos/demo_xor_list.cpp`
- `Semana3/benchmarks/benchmark_semana3.cpp`
- `Semana3/lecturas/Lectura7-Morin.md`

Responde:

1. Compara `ArrayDeque` y `LinkedDeque`: ¿qué cambia en representación y qué cambia en costo observable?
Representación: ArrayDeque guarda los elementos en un arreglo circular contiguo (a[], índice de inicio j, tamaño n). LinkedDeque usa una lista doblemente enlazada (nodos con prev y next) normalmente con un nodo centinela dummy.

Costo observable:
- ArrayDeque: addFirst/addLast, removeFirst/removeLast y get/set son O(1) amortizado (por posible redoblado/copia del arreglo) y muy rápidos en práctica por buena localidad.
- LinkedDeque: las mismas operaciones en extremos son O(1) worst‑case (solo cambios de punteros), pero get(i)/set(i,x) son O(1+min(i,n‑i)) porque requieren recorrer desde la cabeza o la cola.

2. ¿Qué significa que una representación contigua tenga mejor localidad de memoria?
Mejor localidad de memoria significa que los elementos vecinos en el índice lógico están ubicados en direcciones de memoria contiguas. Así, al acceder a una posición, es probable que las siguientes o previas ya estén cargadas en la misma línea de caché, reduciendo fallos de caché y acelerando recorridos secuenciales o accesos por índice.

3. ¿Qué tipo de operaciones favorecen más a la representación enlazada?
Operaciones que favorecen más a la representación enlazada son aquellas que requieren inserciones o eliminaciones frecuentes en el medio o en extremos cuando ya se tiene un puntero al nodo de trabajo (p.ej., splice, concatenar listas, eliminar un nodo dado).

4. En el benchmark, ¿qué comparación sirve mejor para discutir acceso aleatorio y cuál sirve mejor para discutir operaciones en extremos?
En el benchmark:
- La comparación de get(i) (p.ej., ArrayDeque get(4) vs DLList get(4)) sirve para discutir acceso aleatorio por índice.
- La comparación de operaciones en extremos (p.ej., addFirst/addLast, removeFirst/removeLast, o las equivalentes de cola/pila) sirve para discutir operaciones en extremos.

5. ¿Por qué el benchmark no debe leerse como prueba absoluta de superioridad de una estructura sobre otra?
Por qué el benchmark no es una prueba absoluta, mide solo una carga de trabajo específica y tamaños de entrada limitados. Los resultados dependen de factores constantes (costos de asignación, de XOR, de caché, del compilador) que pueden variar entre máquinas y no revelan el comportamiento asintótico.
No explora todas las posibles mezclas de operaciones (p.ej., muchas inserciones en medio) ni casos frontera (lista vacía, un solo elemento). Por lo tanto, no se puede concluir que una estructura sea universalmente superior; solo indica cuál puede ser más rápida bajo esas condiciones particulares.

6. ¿Qué idea intenta mostrar `XorList` respecto al ahorro de punteros?
XorList intenta demostrar que, al almacenar en cada nodo el XOR de las direcciones del nodo anterior y del siguiente, se puede recorrer la lista en ambas direcciones manteniendo solo un campo de puntero por nodo (en lugar de dos). Esto reduce a la mitad el uso de memoria destinado a punteros mientras se conserva la capacidad de movimiento bidireccional.

7. ¿Qué desventaja práctica introduce una estructura como `XorList` aunque sea interesante desde el punto de vista del espacio?
La desventaja práctica de XorList es que para avanzar o retroceder se necesita conocer la dirección del nodo previamente visitado (o llevar un puntero adicional), lo que complica las operaciones de inserción, eliminación y depuración. Además, el código es menos intuitivo y no se beneficia de optimizaciones estándar de punteros; en la práctica el overhead de las operaciones XOR y la necesidad de estado extra suelen hacer que la estructura sea más lenta y más propensa a errores que una lista doblemente enlazada convencional, pese a su ventaja teórica de espacio.

#### Bloque 8 - Cierre comparativo y preparación de sustentación

Responde esta pregunta final:

¿Qué cambia cuando pasamos de "usar arreglos dinámicos" a "diseñar estructuras enlazadas y adaptadores sobre nodos"?

- Representación: pasamos de un bloque contiguo único con campos _size/_capacity a una colección de nodos asignados dinámicamente (cada uno con dato y punteros next/prev) encabezados por head/tail o un nodo centinela dummy.
- Acceso: el acceso por rango (número de predecesores) deja de ser una fórmula aritmética y pasa a requerir recorrido de enlaces, haciendo que get(i) sea O(1) en arreglos contiguos pero O(1+min(i,n-i)) en DLList u O($\sqrt{n}$) en SEList; sin embargo, una vez localizado el nodo, las inserciones y eliminaciones locales son solo cambios de punteros (O(1)), evitando los desplazamientos costosos de los arreglos.
- Complejidad: SLList brinda O(1) en push/pop/peek/add al final y O(n) en get; DLList ofrece O(1) en operaciones en los extremos y O(1+min(i,n-i)) en get/set/add/remove en cualquier posición; SEList mantiene O(1) amortizado en inserciones/extracciones en los extremos y O($\sqrt{n}$) en acceso por índice gracias a sus bloques; los adaptadores (LinkedStack, LinkedQueue, LinkedDeque) y los puentes (Morin‑Deng Bridge) reutilizan el código de nodos existentes para ofrecer nuevas interfaces sin reescribir la estructura subyacente, mostrando que las representaciones contiguas destacan en localidad de memoria y acceso aleatorio rápido, mientras que las enlazadas destacan en flexibilidad de modificaciones locales y estabilidad de referencias.
