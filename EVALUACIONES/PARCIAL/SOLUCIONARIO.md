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

**b) [0.7 pts]** Compare el costo de `insert`, `erase`, `moveLeft`, `moveRight` y `current` para **A** y **B**. Justifique cada entrada de la tabla.

**c) [0.6 pts]** Indique dos invariantes de representación para cada alternativa.

**d) [0.6 pts]** Si el patrón de uso tiene muchas ediciones locales alrededor del cursor y pocas consultas por índice, elija una representación y defienda la elección.

**e) [0.6 pts]** Explique un caso borde que pueda romper cada implementación si no se maneja explícitamente.

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

**b) [0.7 pts]** Justifique la correctitud usando la propiedad `gcd(a,b) = gcd(b, a mod b)`. Debe explicar cómo se conserva el valor buscado.

**c) [0.4 pts]** Justifique terminación.

**d) [0.5 pts]** Indique precondiciones razonables para evitar ambigüedades con números negativos o ambos argumentos cero.

**e) [0.9 pts]** Compare con un algoritmo que prueba todos los divisores desde `min(a,b)` hacia abajo. Analice costo y explique por qué pasar pruebas pequeñas no demuestra eficiencia.

---

## Pregunta 3 (3 pts)

Un `DengVector` mantiene `_elem`, `_size` y `_capacity`. En `insert(i,x)`, si hay capacidad, desplaza a la derecha los elementos en posiciones `i, i+1, ..., size-1`. Si no hay capacidad, primero duplica la capacidad y copia los elementos.

**a) [0.6 pts]** Para `size = 7`, `capacity = 8`, calcule el costo de `insert(0,x)`, `insert(3,x)` y `insert(7,x)` sin redimensionamiento. Justifique en términos de desplazamientos.

**b) [0.6 pts]** Repita para `size = 8`, `capacity = 8`, considerando el costo de copiar al nuevo arreglo y luego desplazar. No olvide la escritura de `x`.

**c) [0.6 pts]** Explique por qué `pushBack` puede ser amortizado `O(1)`, pero `insert(0,x)` no lo es bajo la misma representación.

**d) [0.5 pts]** Indique un invariante que involucre `_size`, `_capacity` y posiciones válidas de `_elem`.

**e) [0.7 pts]** Proponga una política de expand/shrink y explique cómo afecta memoria desprendida y número de copias.

---

## Pregunta 4 (3 pts)

Una `ArrayQueue` circular usa un arreglo de longitud 10, índice `j` del primer elemento y tamaño `n`. El elemento lógico `k` está en `a[(j+k) mod 10]`. Inicialmente `j = 7`, `n = 5`, y el contenido lógico es `[4, 8, 15, 16, 23]`.

**a) [0.5 pts]** Dibuje el estado físico inicial.

**b) [0.6 pts]** Aplique `add(42)`, `remove()`, `add(7)`, `add(9)`, `remove()` y muestre `j`, `n`, contenido lógico y posiciones físicas ocupadas.

**c) [0.5 pts]** Explique por qué el módulo es necesario y qué error aparece si se usa simplemente `j + k`.

**d) [0.7 pts]** Compare `ArrayQueue` con una cola implementada mediante `ArrayList` que elimina siempre en posición 0. Analice costos.

**e) [0.7 pts]** Explique cómo `DualArrayList` combina dos arreglos y por qué necesita rebalanceo. Indique qué propiedad debe mantener el rebalanceo.

---

## Pregunta 5 (3 pts)

Una `DLLList<T>` usa nodo centinela `dummy`, donde `dummy.next` apunta al primer nodo real y `dummy.prev` al último. Si la lista está vacía, ambos apuntan a `dummy`.

**a) [0.6 pts]** Escriba pseudocódigo de `addBefore(Node* w, T x)` actualizando todos los enlaces necesarios.

**b) [0.5 pts]** Explique por qué el nodo centinela elimina casos especiales al insertar al inicio o al final.

**c) [0.5 pts]** Justifique por qué `getNode(i)` puede implementarse en \( O(1 + \min\{i, n - i\}) \).

**d) [0.7 pts]** Diseñe `rotate(r)` que rota la lista `r` posiciones a la derecha sin mover los datos elemento por elemento. Puede describir los cambios de enlaces.

**e) [0.7 pts]** Proponga dos invariantes estructurales que permitan detectar errores de punteros en una prueba tipo `checkSize()` o recorrido doble.

---

## Pregunta 6 (2 pts)

Se desea probar una implementación de `isBalanced(string s)` que acepta paréntesis, corchetes y llaves: `( )`, `[ ]` y `{ }`. Debe retornar `true` si toda apertura se cierra en orden correcto.

**a) [0.8 pts]** Proponga **0** casos de prueba con salida esperada. Deben incluir cadena vacía, anidamiento correcto, cruce incorrecto, cierre sin apertura y apertura sin cierre.

**b) [0.5 pts]** Explique qué error específico detecta cada grupo de pruebas.

**c) [0.4 pts]** Indique el ADT adecuado para resolver el problema y justifique por qué.

**d) [0.3 pts]** Analice complejidad temporal y espacial.

---

## Pregunta 7 (3 pts)

Se recibe un flujo de enteros y se desea responder, para cada posición, el mínimo de los últimos \( k \) elementos procesados. Por ejemplo, para una ventana deslizante de tamaño \( k \). Diseñe un algoritmo usando estructuras estudiadas.

**a) [0.4 pts]** Defina claramente la entrada, la salida y las precondiciones sobre \( k \).

**b) [0.6 pts]** Proponga una representación basada en una cola/deque auxiliar que mantenga candidatos a mínimo.

**c) [0.6 pts]** Dé los invariantes de la estructura auxiliar.

**d) [0.6 pts]** Trace su algoritmo para la secuencia \([5, 2, 4, 1, 3, 0, 6]\) con \( k = 3 \).

**e) [0.5 pts]** Justifique complejidad total y costo amortizado por elemento.

**f) [0.3 pts]** Compare con recalcular el mínimo recorriendo la ventana en cada posición.