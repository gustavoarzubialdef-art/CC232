# CC232 - Evaluación Parcial 1
## Semanas 0, 1, 2 y 3: Fundamentos, arreglos dinámicos y listas
### Versión B

**Puntaje:** 20 puntos  
**Código:** 20230205H  
**Duración:** 3 horas  
**Nombre:** Gustavo Anthony Arzubialde Fierro

> Durante la evaluación queda estrictamente prohibido el uso de celulares, audífonos Bluetooth o cualquier tipo de audiofono, laptops, tablets, relojes inteligentes, cualquier otro dispositivo electrónico, apuntes, materiales impresos o digitales, y herramientas de inteligencia artificial. Los estudiantes deberán contar únicamente con su lapicero y con los conocimientos que hayan adquirido, practicado y repasado durante el curso.  
>  
> Todas las respuestas deberán incluir la justificación correspondiente. En cada pregunta se deberán responder todos los ítems solicitados. No justificar una respuesta o no responder una parte de la pregunta implicará la calificación de 0 en dicha pregunta o ítem, según corresponda. Si escribe código, se evaluará la lógica, los casos borde, los invariantes y la complejidad; no solo la forma sintáctica.

---

## Pregunta 1 (3 pts)

Un editor de texto simplificado expone el ADT `CursorBuffer`:

```cpp
class CursorBuffer {
public:
    void insert(char c);     // inserta en la posición del cursor
    char erase();            // elimina el caracter bajo el cursor
    void moveLeft();
    void moveRight();
    char current() const;
    int size() const;
};
```

Se proponen dos representaciones:
**A:** un arreglo dinámico con índice de cursor;
**B:** una lista doblemente enlazada con nodo centinela y un puntero al nodo del cursor.

**a) [0.5 pts]** Identifique con precisión qué especifica el ADT y qué queda abierto a la implementación.

El ADT especifica las operaciones visibles:
- $insert(c)$ inserta un carácter en la posición del cursor.
- $erase()$ elimina el carácter bajo el cursor.
- $moveLeft()$ y $moveRight()$ mueven el cursor una posición a la izquierda o a la derecha.
- $current()$ devuelve el carácter actual bajo el cursor.
- $size()$ devuelve el número de caracteres almacenados.

Queda abierto a la implementación:
- la estructura interna podría ser un arreglo dinámico o lista doblemente enlazada.
- si $size()$ se mantiene como contador o se calcula al vuelo.
- el manejo de casos extremos como cursor en los límites, buffer vacío.
- detalles de memoria y redimensionamiento.

**b) [0.7 pts]** Compare el costo de `insert`, `erase`, `moveLeft`, `moveRight` y `current` para **A** y **B**. Justifique cada entrada de la tabla.

| Operación | Arreglo dinámico (A) | Lista doblemente enlazada (B) |
|---|---|---|
| insert | O(n) | O(1) |
| erase | O(n) | O(1) |
| moveLeft | O(1) | O(1) |
| moveRight | O(1) | O(1) |
| current | O(1) | O(1) |

Justificación:
- En la representación A, insertar o borrar en la posición del cursor requiere desplazar todos los elementos a la derecha o a la izquierda desde el cursor hasta el final, lo que toma tiempo proporcional al tamaño.
- En B, con el cursor apuntando al nodo actual, insertar o borrar solo cambia un número constante de punteros del nodo actual y sus vecinos.
- $moveLef()$ y $moveRight()$ solo actualizan el índice o el puntero del cursor.
- $current()$ accede directamente al elemento actual ya localizado.

**c) [0.6 pts]** Indique dos invariantes de representación para cada alternativa.

Para la alternativa A:
1. $0 <= cursorIndex <= size$ y el cursor siempre apunta a una posición válida del arreglo lógico.
2. $capacity >= size$.

Para la alternativa B:
1. $dummy.next$ apunta al primer nodo real o a $dummy$ si la lista está vacía.
2. $dummy.prev$ apunta al último nodo real o a $dummy$ si la lista está vacía.

**d) [0.6 pts]** Si el patrón de uso tiene muchas ediciones locales alrededor del cursor y pocas consultas por índice, elija una representación y defienda la elección.

Me parece que la representación más adecuada es la B (lista doblemente enlazada) porque:
- la lista maneja eficientemente inserciones y eliminaciones frecuentes junto al cursor, además tienen costo $O(1)$ sin desplazar bloques de datos.
- el patrón de uso con pocas consultas por índice no necesita un acceso aleatorio eficiente.

**e) [0.6 pts]** Explique un caso borde que pueda romper cada implementación si no se maneja explícitamente.

Para A:
- $moveRight()$ en el extremo derecho si no se verifica **cursorIndex < size** puede salir del rango del arreglo.

Para B:
- $current()$ o $erase()$ cuando la lista está vacía y el cursor no apunta a un nodo real.

---

## Pregunta 2 (3 pts)

Considere el algoritmo de Euclides:

```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```

**a) [0.5 pts]** Trace `gcd(252,105)` mostrando `a`, `b` y `r`.

| Iteración | a   | b   | r = a % b |
|---|---|---|---|
| 1 | 252 | 105 | 42 |
| 2 | 105 | 42 | 21 |
| 3 | 42 | 21 | 0 |
| 4 | 21 | 0 | - |

Resultado: $gcd(252,105) = 21$.

**b) [0.7 pts]** Justifique la correctitud usando la propiedad `gcd(a,b) = gcd(b, a mod b)`. Debe explicar cómo se conserva el valor buscado.

Un algoritmo es correcto si cumple 2 cosas:

1. Corrección parcial
El algoritmo mantiene la siguiente condición en cada iteración: $\gcd(a, b)$ permanece constante (Invariante)

- Inicialmente, $\gcd(a, b)$ es el MCD de los valores de entrada.
- En cada paso, se reemplaza $(a, b)$ por $(b, a \bmod b)$.
- Por la propiedad $\gcd(a, b) = \gcd(b, a \bmod b)$, el MCD no cambia.
- Por lo tanto, el invariante se cumple en todas las iteraciones.

2. Terminación
- En cada iteración, el nuevo valor de $b$ es el residuo $r = a \bmod b$, que satisface $0 \leq r < b$.
- Esto implica que la secuencia de valores de $b$ es estrictamente decreciente y no negativa.
- Eventualmente, $b$ llega a 0, y el bucle termina.

**c) [0.4 pts]** Justifique terminación.

- En cada iteración, el nuevo valor de $b$ es el residuo $r = a \bmod b$, que satisface $0 \leq r < b$.
- Esto implica que la secuencia de valores de $b$ es estrictamente decreciente y no negativa.
- Eventualmente, $b$ llega a 0, y el bucle termina.

**d) [0.5 pts]** Indique precondiciones razonables para evitar ambigüedades con números negativos o ambos argumentos cero.

- $a >= 0$ y $b >= 0$ para evitar ambigüedad con residuos negativos.
- no permitir $a == 0$ && $b == 0$, porque $gcd(0,0)$ no está bien definido en matemáticas.

**e) [0.9 pts]** Compare con un algoritmo que prueba todos los divisores desde `min(a,b)` hacia abajo. Analice costo y explique por qué pasar pruebas pequeñas no demuestra eficiencia.

Algoritmo de prueba de divisores:
- calcular $m = min(a,b)$.
- probar $d = m, m-1, ..., 1$ y devolver el primer $d$ que divide a ambos.

Costo:
- en el peor caso recorre hasta $min(a,b)$ valores.
- si $a$ y $b$ son grandes, esto resulta muy lento.

El algoritmo de Euclides es mucho más eficiente porque reduce los valores rápidamente.

Las pruebas pequeñas no demuestran eficiencia porque:
- con números pequeños ambos algoritmos pueden parecer rápidos.
- la eficiencia real se mide en cómo crece el tiempo con el tamaño de los datos.
- un algoritmo que pasa ejemplos pequeños puede fallar en casos grandes o específicos donde su costo explota.

---

## Pregunta 3 (3 pts)

Un `DengVector` mantiene `_elem`, `_size` y `_capacity`. En `insert(i,x)`, si hay capacidad, desplaza a la derecha los elementos en posiciones `i, i+1, ..., size-1`. Si no hay capacidad, primero duplica la capacidad y copia los elementos.

**a) [0.6 pts]** Para `size = 5`, `capacity = 6`, calcule el costo de `insert(0,x)`, `insert(3,x)` y `insert(7,x)` sin redimensionamiento. Justifique en términos de desplazamientos.

- $insert(0,x)$: mueve los elementos en posiciones $0..4$ una casilla a la derecha, son $5$ desplazamientos.
- $insert(3,x)$: mueve los elementos en posiciones $3$ y $4$, son $2$ desplazamientos.

Cada desplazamiento corresponde a una copia de un elemento, por lo que el costo es proporcional a **size - i**.

**b) [0.6 pts]** Repita para `size = 6`, `capacity = 7`, considerando el costo de copiar al nuevo arreglo y luego desplazar. No olvide la escritura de `x`.

- $insert(0,x)$: mueve los elementos en posiciones $0..5$, son $6$ desplazamientos.
- $insert(3,x)$: mueve los elementos en posiciones $3..5$, son $3$ desplazamientos.
- $insert(7,x)$: Redimensiona a capacidad $14$, después realiza $6$ copias $+ 0$ desplazamientos $+ 1$ escritura $= 7$ operaciones.

El costo total es **O(size)** porque la copia domina.

**c) [0.6 pts]** Explique por qué `pushBack` puede ser amortizado `O(1)`, pero `insert(0,x)` no lo es bajo la misma representación.

**pushBack** al final solo escribe en la posición **size** cuando hay capacidad. Si no hay capacidad, duplica el arreglo y copia todos los elementos, pero esto ocurre de forma rara: cada elemento se copia un número amortizado constante de veces. Por eso el costo promedio por operación es $O(1)$.

$insert(0,x)$ siempre desplaza todos los elementos existentes hacia la derecha, aun cuando hay capacidad.
Su costo crece proporcionalmente al número de elementos en el vector en cada llamada, por lo que no puede tener un costo amortizado $O(1)$.

**d) [0.5 pts]** Indique un invariante que involucre `_size`, `_capacity` y posiciones válidas de `_elem`.

El invariante:
- **0 <= _size <= _capacity**.
- los elementos válidos están en **_elem[0.._size-1]**.
- las posiciones **_elem[_size.._capacity-1]** pueden estar sin inicializar o contener basura.

**e) [0.7 pts]** Proponga una política de expand/shrink y explique cómo afecta memoria desprendida y número de copias.

Propuesta:
- expand: cuando **_size == _capacity**, duplicar la capacidad: **_capacity *= 2**.
- shrink: cuando **_size <= _capacity / 4**, reducir la capacidad a la mitad: **_capacity /= 2**, manteniendo **_capacity >= 1**.

Efectos:
- reduce la memoria desperdiciada cuando la lista se contrae.
- evita encogimientos frecuentes porque se espera a que el arreglo esté al menos 75% vacío.
- mantiene el número de copias amortizado bajo control; cada elemento se copia pocas veces en el tiempo total.

---

## Pregunta 4 (3 pts)

Una `ArrayQueue` circular usa un arreglo de longitud 10, índice `j` del primer elemento y tamaño `n`. El elemento lógico `k` está en `a[(j+k) mod 10]`. Inicialmente `j = 7`, `n = 5`, y el contenido lógico es `[4, 8, 15, 16, 23]`.

**a) [0.5 pts]** Dibuje el estado físico inicial.

Para $j = 7$ y $n = 5$:
- $a[7] = 4$
- $a[8] = 8$
- $a[9] = 15$
- $a[0] = 16$
- $a[1] = 23$

Los índices libres son $2, 3, 4, 5, 6$.

**b) [0.6 pts]** Aplique `add(42)`, `remove()`, `add(7)`, `add(9)`, `remove()` y muestre `j`, `n`, contenido lógico y posiciones físicas ocupadas.

Estado inicial: $j=7$, $n=5$, lógico $[4,8,15,16,23]$.

$add(42)$:
   - posición física (7+5)%10 = 2.
   - $a[2] = 42$.
   - resultado: $j=7$, $n=6$, lógico $[4,8,15,16,23,42]$.
   - ocupados: $7,8,9,0,1,2$.

$remove()$:
   - elimina $a[7] = 4$.
   - $j = 8$, $n = 5$.
   - lógico: $[8,15,16,23,42]$.
   - ocupados: $8,9,0,1,2$.

$add(7)$:
   - posición física (8+5)%10 = 3.
   - $a[3] = 7$.
   - resultado: $j=8$, $n=6$, lógico $[8,15,16,23,42,7]$.
   - ocupados: $8,9,0,1,2,3$.

$add(9)$:
   - posición física (8+6)%10 = 4.
   - $a[4] = 9$.
   - resultado: $j=8$, $n=7$, lógico $[8,15,16,23,42,7,9]$.
   - ocupados: $8,9,0,1,2,3,4$.

$remove()$:
   - elimina $a[8] = 8$.
   - $j = 9$, $n = 6$.
   - lógico: $[15,16,23,42,7,9]$.
   - ocupados: $9,0,1,2,3,4$.

**c) [0.5 pts]** Explique por qué el módulo es necesario y qué error aparece si se usa simplemente `j + k`.

El módulo es necesario para que el cálculo físico de índice vuelva al inicio del arreglo cuando se supera su longitud. Si se usa $j + k$ sin módulo, el índice puede quedar fuera del rango y producir acceso ilegal. Por ejemplo, con $j=7$ y $k=4$, $j+k = 11$, que no existe en un arreglo de tamaño $10$.

**d) [0.7 pts]** Compare `ArrayQueue` con una cola implementada mediante `ArrayList` que elimina siempre en posición 0. Analice costos.

**ArrayQueue**
- **Enqueue:**
  Se coloca el nuevo elemento en la posición **rear** y se avanza el índice circular.
  **Costo:** $O(1)$.
- **Dequeue:**
  Se toma el elemento en la posición **front** y se avanza el índice circular.
  **Costo:** $O(1)$.
- **Ventaja:** No hay desplazamientos de elementos, solo actualización de índices.

**Cola sobre ArrayStack**
- **Enqueue:**
  Se agrega al final del arreglo.
  **Costo:** $O(1)$.
- **Dequeue:**
  Se elimina el primer elemento, pero para mantener la estructura hay que desplazar todos los demás una posición a la izquierda.
  **Costo:** $O(n)$, donde n es el número de elementos en la cola.
- **Desventaja:** Cada eliminación es costosa por los desplazamientos.

**Conclusión:** la cola circular es significativamente más eficiente para la semántica FIFO, porque evita los desplazamientos costosos en cada extracción.

**e) [0.7 pts]** Explique cómo `DualArrayList` combina dos arreglos y por qué necesita rebalanceo. Indique qué propiedad debe mantener el rebalanceo.

Un **DualArrayDeque** implementa un deque usando dos arreglos dinámicos:

- El arreglo izquierdo almacena la mitad inicial de los elementos (en orden inverso).
- El arreglo derecho almacena la mitad final de los elementos (en orden normal).

De esta forma se pueden realizar operaciones eficientes en ambos extremos:
- Insertar/eliminar al frente se hace en el arreglo izquierdo.
- Insertar/eliminar al final se hace en el arreglo derecho.

**¿Por qué necesita rebalanceo?**

Con el uso, las operaciones pueden desbalancear la estructura:
- Un arreglo puede quedar muy lleno y el otro casi vacío.
- Esto afecta la eficiencia y puede provocar que un arreglo se desborde mientras el otro tiene espacio libre.

El rebalanceo redistribuye los elementos entre los dos arreglos para mantenerlos equilibrados.

**Propiedad que debe mantener el rebalanceo**

El rebalanceo debe garantizar que:
- Los dos arreglos tengan tamaños comparables (ninguno debe ser mucho más grande que el otro).

---

## Pregunta 5 (3 pts)

Una `DLLList<T>` usa nodo centinela `dummy`, donde `dummy.next` apunta al primer nodo real y `dummy.prev` al último. Si la lista está vacía, ambos apuntan a `dummy`.

**a) [0.6 pts]** Escriba pseudocódigo de `addBefore(Node* w, T x)` actualizando todos los enlaces necesarios.

Node* u = new Node;
u->elem = x;
u->next = w;
u->prev = w->prev;
w->prev->next = u;
w->prev = u;
size = size + 1;

**b) [0.5 pts]** Explique por qué el nodo centinela elimina casos especiales al insertar al inicio o al final.

El nodo centinela elimina los casos especiales al insertar al inicio o al final porque:

- **Inserción al inicio:**
  En lugar de verificar si la lista está vacía o si hay que actualizar referencias nulas, siempre se inserta el nuevo nodo entre **dummy** y **dummy.next**.
  El **dummy** garantiza que existe un nodo previo.

- **Inserción al final:**
  De forma similar, el nuevo nodo se inserta entre **dummy.prev** y **dummy**.
  El **dummy** garantiza que existe un nodo siguiente.

**Conclusión:** El nodo centinela actúa como un ancla permanente en ambos extremos de la lista. Gracias a él, las operaciones de inserción y eliminación no necesitan distinguir entre lista vacía, inicio o final, las referencias siempre existen y se actualizan de manera uniforme.

**c) [0.5 pts]** Justifique por qué `getNode(i)` puede implementarse en \( O(1 + \min\{i, n - i\}) \).

En una `DLLList<T>` la estrategia de búsqueda para obtener el nodo en posición **i** es:
- Si **i** está más cerca del inicio, se recorre desde **dummy.next** hacia adelante.
- Si **i** está más cerca del final, se recorre desde **dummy.prev** hacia atrás.

**Costos:**
- Recorrer desde el inicio hasta **i** cuesta **i** pasos.
- Recorrer desde el final hasta **i** cuesta **n - i** pasos, donde **n** es el tamaño de la lista.

En ambos casos hay un costo constante adicional por acceder al centinela y comenzar el recorrido.

**Conclusión:** El tiempo de ejecución es: $O(1 + \min\{i, \, n - i\})$ porque se elige el recorrido más corto entre avanzar desde el inicio o retroceder desde el final.

**d) [0.7 pts]** Diseñe `rotate(r)` que rota la lista `r` posiciones a la derecha sin mover los datos elemento por elemento. Puede describir los cambios de enlaces.

Para rotar la lista `r` posiciones a la derecha sin mover los datos elemento por elemento, se puede aprovechar la estructura doblemente enlazada y el nodo centinela:

1. **Normalización de r:**
   Si **r > n** (donde **n** es el tamaño de la lista), se toma $r = r \bmod n$.

2. **Localización del nuevo inicio y fin:**
   - El nuevo primer nodo será el que actualmente está en la posición **n - r**.
   - El nuevo último nodo será el que actualmente está en la posición **n - r - 1**.

3. **Reajuste de enlaces:**
   - **dummy.next** se actualiza para apuntar al nuevo primer nodo.
   - **dummy.prev** se actualiza para apuntar al nuevo último nodo.
   - El antiguo último nodo conecta con el antiguo primer nodo, cerrando el ciclo.
   - Se actualizan los punteros **prev** y **next** de los nodos involucrados para mantener la doble conexión.

4. **Resultado:**
   La lista queda rotada **r** posiciones a la derecha, manteniendo el orden relativo de los elementos, sin necesidad de copiar datos ni recorrer nodo por nodo.

**e) [0.7 pts]** Proponga dos invariantes estructurales que permitan detectar errores de punteros en una prueba tipo `checkSize()` o recorrido doble.

1. recorriendo la lista desde **dummy.next** con **next** exactamente **size** veces se debe regresar a **dummy**.
2. recorriendo desde **dummy.prev** con **prev** exactamente **size** veces se debe regresar a **dummy**.

---

## Pregunta 6 (2 pts)

Se desea probar una implementación de `isBalanced(string s)` que acepta paréntesis, corchetes y llaves: `( )`, `[ ]` y `{ }`. Debe retornar `true` si toda apertura se cierra en orden correcto.

**a) [0.8 pts]** Proponga **2** casos de prueba con salida esperada. Deben incluir cadena vacía, anidamiento correcto, cruce incorrecto, cierre sin apertura y apertura sin cierre.

1. Anidamiento correcto: **"([{}])"** retorna **true**
2. Cruce incorrecto: **"([)]"** retorna **false**

**b) [0.5 pts]** Explique qué error específico detecta cada grupo de pruebas.

- cadena vacía: detecta el caso donde no hay símbolos de apertura ni de cierre.
- anidamientos correctos: detecta que las aperturas y cierres están en orden válido y bien anidados.
- cruces incorrectos: detecta patrones como `([)]` donde las aperturas y cierres no coinciden en orden.
- cierre sin apertura: detecta casos donde aparece un símbolo de cierre (`)`, `]`, `}`) sin que exista previamente una apertura correspondiente.
- apertura sin cierre: detecta casos donde al final de la cadena quedan símbolos de apertura (`(`, `[`, `{`) que nunca fueron cerrados.

**c) [0.4 pts]** Indique el ADT adecuado para resolver el problema y justifique por qué.

El ADT adecuado es una pila porque:
- los delimitadores se cierran en orden inverso al que se abren.
- cada apertura se apila y cada cierre se compara con el tope.
- el comportamiento LIFO de la pila coincide con el requisito del problema.

**d) [0.3 pts]** Analice complejidad temporal y espacial.

**Complejidad temporal**
- El algoritmo recorre la cadena de izquierda a derecha, examinando cada carácter una sola vez.
- Cada operación de verificación (apertura o cierre) se realiza en tiempo constante.
- Por lo tanto, el tiempo total es proporcional a la longitud de la cadena: $O(n)$ donde $n$ es el número de caracteres en la cadena.

**Complejidad espacial**
- En el peor caso, si la cadena contiene únicamente aperturas, se almacenan todos los caracteres.
- Por lo tanto, el espacio adicional requerido es proporcional al número de caracteres: $O(n)$

---

## Pregunta 7 (3 pts)

Se recibe un flujo de enteros y se desea responder, para cada posición, el mínimo de los últimos \( k \) elementos procesados. Por ejemplo, para una ventana deslizante de tamaño \( k \). Diseñe un algoritmo usando estructuras estudiadas.

**a) [0.4 pts]** Defina claramente la entrada, la salida y las precondiciones sobre \( k \).

**Entrada:**
- una secuencia de enteros $a[0..n-1]$.
- un entero $k$ con el tamaño de la ventana.

**Salida:**
- una secuencia de $n-k+1$ valores donde cada valor es el mínimo de la ventana actual $a[i-k+1..i]$ para $i = k-1..n-1$.

**Precondiciones:**
- $k >= 1$.
- $k <= n$.
- $n >= k$.

**b) [0.6 pts]** Proponga una representación basada en una cola/deque auxiliar que mantenga candidatos a mínimo.

Usar un **deque** que almacene índices de elementos candidatos a mínimo. Para cada nuevo elemento $a[i]$:
1. eliminar del final del **deque** todos los índices $j$ tales que $a[j] > a[i]$, porque $a[i]$ es un mejor candidato y los anteriores ya no pueden ser mínimos mientras **i** esté en la ventana.
2. insertar $i$ al final del **deque**.
3. eliminar del frente del **deque** los índices $j$ que ya no pertenecen a la ventana actual, es decir, $j <= i-k$.
4. el mínimo de la ventana actual es $a[deque.front()]$ cuando $i >= k-1$.

**c) [0.6 pts]** Dé los invariantes de la estructura auxiliar.

1. los índices en el **deque** están en orden estrictamente creciente.
2. los valores correspondientes $a[index]$ son no decrecientes de frente a final.
3. el frente del **deque** siempre referencia el mínimo válido de la ventana actual.
4. ningún índice fuera de la ventana actual permanece en el **deque**.

**d) [0.6 pts]** Trace su algoritmo para la secuencia \([5, 2, 4, 1, 3, 0, 6]\) con \( k = 3 \).

- $i=0$, valor $5$: deque $= [0]$, sin salida.
- $i=1$, valor $2$: quita $0$ porque $5 > 2$, deque $= [1]$.
- $i=2$, valor $4$: deque $= [1,2]$, salida para ventana $[5,2,4]$ → mínimo = $2$.
- $i=3$, valor $1$: quita $2$ y $1$ porque $4 > 1$ y $2 > 1$, deque $= [3]$, salida $[2,4,1]$ → mínimo $= 1$.
- $i=4$, valor $3$: deque $= [3,4]$, salida $[4,1,3]$ → mínimo = $1$.
- $i=5$, valor $0$: quita $4$ y $3$ porque son mayores, quita también $3$ si es necesario, deque $= [5]$, salida $[1,3,0]$ → mínimo $= 0$.
- $i=6$, valor $6$: deque $= [5,6]$, salida $[3,0,6]$ → mínimo = $0$.

Resultados de las ventanas: $[2, 1, 1, 0, 0]$.

**e) [0.5 pts]** Justifique complejidad total y costo amortizado por elemento.

**Complejidad temporal**
Cada elemento se inserta una vez y se elimina del **deque** como máximo una vez. Por lo tanto, el número total de operaciones es proporcional a $n$ (longitud del flujo): $O(n)$

**Costo amortizado por elemento**
Como cada inserción/eliminación ocurre a lo sumo una vez por elemento, el costo promedio es: $O(1)$

**f) [0.3 pts]** Compare con recalcular el mínimo recorriendo la ventana en cada posición.

Recalcular el mínimo para cada ventana recorriendo $k$ elementos daría un costo $O(n*k)$. Cuando $k$ es grande, esto es mucho peor que el algoritmo con **deque**, que es $O(n)$. Por eso el método de ventana deslizante con **deque** es significativamente más eficiente.