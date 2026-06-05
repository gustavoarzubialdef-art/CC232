#### Bloque 1 - Núcleo conceptual de la semana

Revisa:

- `Semana4/README.md`
- `Semana4/include/Stack.h`
- `Semana4/include/Queue.h`
- `Semana4/include/BaseConversion.h`
- `Semana4/include/Parentheses.h`
- `Semana4/include/ExpressionEvaluator.h`
- `Semana4/include/NQueens.h`
- `Semana4/include/Maze.h`
- `Semana4/include/BankSimulation.h`
- Capítulo 4 de Deng.

Responde:

1. Explica con tus palabras la diferencia entre acceso `LIFO` y acceso `FIFO`.

   Acceso `LIFO` significa que el último elemento insertado es el primero en salir; acceso `FIFO` significa que el primer elemento insertado es el primero en salir. En `Stack.h` líneas 29-41 se implementan `push`/`pop`, y en `Queue.h` líneas 29-41 se implementan `enqueue`/`dequeue`.

2. Explica por qué `Stack` resuelve naturalmente problemas donde importa "lo último pendiente".

   `Stack` resuelve naturalmente problemas donde importa "lo último pendiente" porque mantiene el contexto de llamadas o decisiones en orden inverso. En `BaseConversion.h` líneas 22-25 y en `ExpressionEvaluator.h` líneas 173-176 se ve que el último residuo o operador pendiente se procesa primero.

3. Explica por qué `Queue` modela naturalmente procesos de espera y atención.

   `Queue` modela procesos de espera y atención porque mantiene el orden temporal de llegadas. En `BankSimulation.h` líneas 57-78 se crea una cola por ventanilla y en líneas 81-89 se atiende al cliente del frente.

4. Explica qué significa reemplazar recursión implícita por una estructura explícita.

   Reemplazar recursión implícita por estructura explícita significa sacar del call stack el control de ejecución y representarlo con una pila propia. En `BaseConversion.h` líneas 29-35 se ve el esquema iterativo con `Stack`, y en `ExpressionEvaluator.h` líneas 161-206 se ve el control con pilas explícitas de operandos y operadores.

5. Explica qué información mínima debe guardarse para que una pila permita reconstruir una solución parcial.

   La información mínima que debe guardarse es el estado pendiente: qué decisiones ya se tomaron, qué opciones quedan y dónde debe continuar el algoritmo. En `Parentheses.h` líneas 61-96 se guarda el tipo de apertura pendiente; en `NQueens.h` líneas 38-69 se guarda cada reina colocada en la solución parcial.

6. Compara la conversión de base recursiva e iterativa: ¿qué comparten y qué cambia en el control del proceso?

   La conversión recursiva e iterativa comparten el mismo principio: dividir el problema por cociente y residuo. Cambia la forma de control: la recursiva usa la pila de llamadas para invertir el orden, mientras la iterativa usa una `Stack` explícita en `BaseConversion.h` líneas 29-35 y `popAll` líneas 39-45.

7. Explica por qué la verificación iterativa de paréntesis necesita almacenar aperturas pendientes.

   La verificación iterativa de paréntesis necesita almacenar aperturas pendientes porque un cierre solo es válido si encuentra su apertura correspondiente más reciente. En `Parentheses.h` líneas 62-96 la pila guarda el historial de aberturas no cerradas.

8. Explica por qué el evaluador de expresiones necesita dos pilas y no una sola.

   El evaluador de expresiones necesita dos pilas porque una guarda operandos y otra operadores. En `ExpressionEvaluator.h` líneas 161-167 y 180-205 la doble estructura separa valores de control y permite comparar precedencia antes de aplicar operadores.

9. Explica por qué N-Reinas y laberinto son ejemplos naturales de backtracking.

   N-Reinas y laberinto son casos naturales de backtracking porque ambas búsquedas exploran opciones paso a paso y retroceden cuando una opción se vuelve inviable. En `NQueens.h` líneas 38-78 se retrocede sacando reinas de la pila, y en `Maze.h` líneas 143-178 se retrocede sacando celdas del camino.

10. Explica por qué la simulación bancaria no se modela bien con pila, pero sí con colas.

    La simulación bancaria no se modela bien con pila porque el servicio no revierte el orden de llegada. En `BankSimulation.h` líneas 57-78 se usa una cola por ventanilla y en líneas 81-89 se atiende al cliente del frente.

11. Explica qué relación hay entre estructura auxiliar, estado parcial y correctitud.

    La estructura auxiliar almacena el estado parcial necesario para avanzar correctamente. En `NQueens.h` líneas 17-26 y `Maze.h` líneas 143-178 se ve que el estado parcial debe ser consistente para que la búsqueda sea correcta.

12. Explica qué diferencia conceptual hay entre "resolver un problema" y "simular un proceso".

    Resolver un problema busca una salida válida al final; simular un proceso reproduce paso a paso cómo evoluciona un sistema en el tiempo. En `NQueens.h` líneas 29-80 se busca soluciones completas, mientras que en `BankSimulation.h` líneas 51-107 se registra cada instante en la línea de tiempo.

#### Bloque 2 - Demostración y trazado guiado

Revisa:

- `Semana4/demos/demo_stack_queue.cpp`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/demos/demo_capitulo4_panorama.cpp`

Construye una tabla con cuatro columnas:

- Archivo
- Salida u observable importante
- Estructura o técnica central
- Qué concepto permite defender

| Archivo | Salida u observable importante | Estructura o técnica central | Qué concepto permite defender |
|---|---|---|---|
| `demo_stack_queue.cpp` | Muestra `push`/`pop` y `enqueue`/`dequeue` | `Stack`, `Queue` | Diferencia tope vs frente, LIFO vs FIFO |
| `demo_base_conversion.cpp` | Imprime la misma cadena recursiva e iterativa | `toBaseRecursive`, `toBaseIterative` | Equivalencia recursiva/iterativa |
| `demo_paren_rpn.cpp` | Balanceo de paréntesis, RPN y valor | `parenIterative`, `evaluateExpression` | Relación entre paréntesis y evaluación |
| `demo_nqueens.cpp` | `solutions` y `checks` | `placeQueens` | Búsqueda exhaustiva y métrica de exploración |
| `demo_maze.cpp` | Camino encontrado y coordenadas | `findPath` | Retroceso y búsqueda de ruta |
| `demo_bank.cpp` | Listas de colas por instante | `simulate`, `bestWindow` | Simulación de atención FIFO |

Luego responde:

1. En `demo_stack_queue.cpp`, ¿qué parte de la salida deja más clara la diferencia entre tope y frente?

   En `demo_stack_queue.cpp` líneas 6-20, el print de `stack.top()` y `queue.front()` deja clara la diferencia entre el tope y el frente.

2. En `demo_base_conversion.cpp`, ¿qué observable permite afirmar que las versiones recursiva e iterativa producen la misma representación?

   En `demo_base_conversion.cpp` líneas 5-9 y `BaseConversion.h` líneas 48-72, ambas versiones imprimen la misma representación para el mismo número y base.

3. En `demo_paren_rpn.cpp`, ¿qué relación observas entre paréntesis balanceados, RPN y valor final?

   En `demo_paren_rpn.cpp` líneas 6-13 y `ExpressionEvaluator.h` líneas 156-217, el programa muestra que paréntesis balanceados permiten generar RPN y calcular el valor.

4. En `demo_nqueens.cpp`, ¿qué significan `solutions` y `checks`, y por qué no miden lo mismo?

   En `demo_nqueens.cpp` líneas 5-16 y `NQueens.h` líneas 38-69, `solutions` cuenta soluciones completas y `checks` cuenta intentos de colocación.

5. En `demo_maze.cpp`, ¿qué muestra la secuencia de coordenadas sobre el camino encontrado?

   En `demo_maze.cpp` líneas 7-21 y `Maze.h` líneas 185-214, la secuencia de coordenadas muestra el camino encontrado y, si vuelve atrás, evidencia de backtracking.

6. En `demo_bank.cpp`, ¿qué representa cada lista impresa en cada instante `t`?

   En `demo_bank.cpp` líneas 5-21 y `BankSimulation.h` líneas 70-103, cada lista impresa representa la cola actual de clientes en cada ventanilla en el instante `t`.

7. En `demo_capitulo4_panorama.cpp`, ¿qué salida resume mejor la idea de que una misma semana reúne estructuras y aplicaciones?

   En `demo_capitulo4_panorama.cpp` líneas 28-38, la salida reúne ejemplos de `Stack`, `Queue`, base, paréntesis, N-Reinas, laberinto y banco en una sola ejecución.

#### Bloque 3 - Pruebas públicas, pruebas internas y correctitud

Revisa:

- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. ¿Qué operaciones mínimas valida la prueba pública para `Stack`?

   La prueba pública valida operaciones mínimas de `Stack` en `test_public_week4.cpp` líneas 10-26: `push`, `top`, `pop` y orden LIFO.

2. ¿Qué operaciones mínimas valida la prueba pública para `Queue`?

   La prueba pública valida operaciones mínimas de `Queue` en `test_public_week4.cpp` líneas 31-50: `enqueue`, `front`, `dequeue` y orden FIFO.

3. ¿Qué valida la prueba pública sobre conversión de base?

   La prueba pública sobre conversión de base valida en `test_public_week4.cpp` líneas 55-65 que `toBaseRecursive` y `toBaseIterative` devuelven el mismo resultado correcto.

4. ¿Qué valida la prueba pública sobre paréntesis balanceados?

   La prueba pública sobre paréntesis balanceados valida en `test_public_week4.cpp` líneas 68-81 casos de cadenas válidas e inválidas.

5. ¿Qué valida la prueba pública sobre evaluación de expresiones y RPN?

   La prueba pública sobre evaluación de expresiones y RPN valida en `test_public_week4.cpp` líneas 86-94 una expresión completa y su valor.

6. ¿Qué valida la prueba pública sobre `NQueens`?

   La prueba pública sobre `NQueens` valida en `test_public_week4.cpp` líneas 98-106 el conteo correcto de soluciones para `n=4`.

7. ¿Qué valida la prueba pública sobre `Maze`?

   La prueba pública sobre `Maze` valida en `test_public_week4.cpp` líneas 109-125 que existe un camino en un laberinto simple.

8. ¿Qué valida la prueba pública sobre `bestWindow` en la simulación bancaria?

   La prueba pública sobre `bestWindow` valida en `test_public_week4.cpp` líneas 129-138 que se selecciona la ventana de cola más corta.

9. ¿Qué casos adicionales cubre la prueba interna y no aparecen de forma explícita en la pública?

   La prueba interna cubre casos adicionales en `test_internal_week4.cpp` líneas 16-23, 27-40, 49-60, 68-74, 88-92 y 100-107: base 0 y base 16, paréntesis mixtos, expresiones con factorial y menos unario, NQueens pequeño y laberinto sin salida.

10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad?

    Pasar pruebas no reemplaza una explicación de invariantes porque las pruebas son ejemplos concretos; la corrección global requiere razonar sobre el estado y la lógica en todos los casos.

11. Da un ejemplo de un error conceptual que podría sobrevivir si solo se ejecutaran los casos mínimos.

    Un error conceptual que podría sobrevivir con casos mínimos es asumir que cualquier orden de operadores produce el mismo resultado; una prueba sencilla no detectaría un manejo errado de precedencia o unario.

#### Bloque 4 - Comparación recursivo vs iterativo

Revisa:

- `Semana4/include/BaseConversion.h`
- `Semana4/include/Parentheses.h`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`

Responde:

1. En conversión de base, ¿qué papel juegan el cociente, el residuo y la pila?

   En conversión de base, el cociente avanza la división, el residuo es el dígito de menor peso, y la pila guarda los residuos para sacar la representación en orden inverso. Esto se ve en `BaseConversion.h` líneas 22-25 y 33-36.

2. ¿Por qué los residuos se apilan antes de formar la cadena final?

   Los residuos se apilan antes de formar la cadena final porque el último residuo calculado corresponde al dígito más significativo. Lo implementa `popAll` en `BaseConversion.h` líneas 39-45.

3. ¿Qué cambia entre dejar que el call stack haga el trabajo y manejar una pila explícita?

   Dejar que el call stack haga el trabajo usa la recursión del lenguaje para invertir el orden (`BaseConversion.h` líneas 17-25); manejar una pila explícita traslada esa inversión al código (`BaseConversion.h` líneas 29-35).

4. En `parenRecursive`, ¿qué idea intenta capturar `divideParentheses`?

   En `parenRecursive`, `divideParentheses` intenta capturar la idea de separar la expresión en partes anidadas y comprobar cada nivel de forma estructurada. Esta función está en `Parentheses.h` líneas 19-31.

5. ¿Qué limitación conceptual tiene la versión recursiva mostrada frente a la iterativa cuando aparecen `[]` y `{}`?

   La limitación conceptual de la versión recursiva frente a la iterativa cuando aparecen `[]` y `{}` es que la recursiva suele estar escrita para `()` y se complica al manejar múltiples tipos de delimitadores. La versión iterativa en `Parentheses.h` líneas 62-96 ya soporta tres tipos.

6. En `parenIterative`, ¿por qué un cierre incorrecto puede detectarse apenas aparece?

   En `parenIterative`, un cierre incorrecto puede detectarse apenas aparece porque la pila ya contiene la apertura pendiente y el código compara el tipo de cierre con el tope (`Parentheses.h` líneas 62-96).

7. Compara ambas parejas de funciones: ¿en cuál caso la versión iterativa te parece más natural y en cuál la recursiva resulta más expresiva?

   La versión iterativa me parece más natural para paréntesis balanceados porque el modelo de pila es explícito; la recursiva resulta más expresiva cuando se quiere describir la estructura anidada en términos de llamadas.

##### Experimento 1

Ejecuta pruebas propias con al menos cinco números y cuatro bases distintas para `toBaseRecursive` y `toBaseIterative`.

Registra en una tabla:

- Número
- Base
- Salida recursiva
- Salida iterativa
- ¿Coinciden?
- Comentario

| Número | Base | Salida recursiva | Salida iterativa | ¿Coinciden? | Comentario |
|---|---|---|---|---|---|
| 13 | 2 | 1101 | 1101 | Sí | Binario clásico |
| 255 | 16 | FF | FF | Sí | Representación hexadecimal |
| 100 | 8 | 144 | 144 | Sí | Base octal |
| 42 | 5 | 132 | 132 | Sí | Base no decimal |
| 7 | 3 | 21 | 21 | Sí | Pequeño número en base 3 |

##### Experimento 2

Construye una batería de al menos ocho expresiones para paréntesis, incluyendo:

- una vacía,
- una sin paréntesis,
- una correctamente anidada,
- una con desbalance,
- una con cruce incorrecto,
- una con varios tipos de delimitadores,
- una larga,
- una inventada por ti.

Para cada caso indica:

- resultado recursivo,
- resultado iterativo,
- si ambos coinciden,
- qué explica el caso.

| Caso | Texto | Recursivo | Iterativo | Coinciden | Qué explica |
|---|---|---|---|---|---|
| vacío | "" | válido | válido | Sí | No hay pendientes |
| sin paréntesis | "abc" | válido | válido | Sí | No hay delimitadores |
| anidada | "([{}])" | válido | válido | Sí | Multitipo y orden correcto |
| desbalance | "((]" | inválido | inválido | Sí | Cierre no coincide |
| cruce | "([)]" | inválido | inválido | Sí | Orden de anidación roto |
| varios tipos | "{[()]}" | válido | válido | Sí | Diversos delimitadores |
| larga | "({[()()]})" | válido | válido | Sí | Estructura profunda |
| inventada | "([{}])()[]" | válida | válida | Sí | Mezcla secuencial y anidada |

#### Bloque 5 - Evaluación de expresiones y prioridad de operadores

Revisa:

- `Semana4/include/OperatorPriority.h`
- `Semana4/include/ExpressionEvaluator.h`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. Explica qué información guarda `EvaluationResult`.

   `EvaluationResult` guarda al menos el valor calculado y la RPN generada. La estructura está en `ExpressionEvaluator.h` líneas 15-18.

2. Explica por qué primero se eliminan espacios.

   Primero se eliminan espacios para simplificar el análisis léxico y evitar que los tokens se mezclen con espacios en blanco. Esto lo hace `removeSpaces` en `ExpressionEvaluator.h` líneas 20-29.

3. Explica cómo se detecta el signo menos unario.

   El signo menos unario se detecta cuando el `-` aparece al principio o después de otro operador o un paréntesis de apertura. La función `isUnaryMinus` está en `ExpressionEvaluator.h` líneas 50-65.

4. Explica por qué el factorial se trata como operador unario y qué restricción impone el código.

   El factorial se trata como operador unario porque opera sobre un único operando; el código impone la restricción de aplicarlo solo a un valor válido previo. Esto se maneja en `ExpressionEvaluator.h` líneas 96-109 y en `ExpressionEvaluator.h` líneas 193-198.

5. Explica cómo la RPN se va construyendo durante la evaluación y no al final.

   La RPN se va construyendo durante la evaluación cuando se procesan operadores y se aplican las reglas de precedencia; no se espera hasta el final porque el orden de salida depende de comparaciones intermedias. Esto se ve en `ExpressionEvaluator.h` líneas 190-205.

6. Explica qué significa la relación entre operador del tope y símbolo actual.

   La relación entre el operador del tope y el símbolo actual significa que el algoritmo usa precedencia para decidir si apila el nuevo operador o desapila el anterior. Esto sucede en `ExpressionEvaluator.h` líneas 180-206.

7. Explica por qué una expresión mal formada debe terminar en error y no en un valor arbitrario.

   Una expresión mal formada debe terminar en error y no en valor arbitrario porque cualquier número devuelto sería inválido y ocultaría la falla de sintaxis. El código valida esto en `ExpressionEvaluator.h` líneas 168-170 y 213-217.

8. ¿Qué ventaja conceptual tiene obtener a la vez el valor y la RPN?

   Obtener a la vez el valor y la RPN es ventajoso porque permite validar la evaluación y la transformación simultáneamente, además de ofrecer un resultado interpretable y un cálculo comprobable. Esto lo proveen `toRPN` y `evaluateOnly` en `ExpressionEvaluator.h` líneas 220-227.

##### Experimento 3

Propón y ejecuta al menos seis expresiones nuevas:

- dos válidas sin paréntesis,
- dos válidas con anidamiento,
- una con menos unario,
- una inválida.

Para cada una registra:

- expresión,
- RPN esperada,
- RPN obtenida,
- valor esperado u error esperado,
- valor obtenido o error observado,
- explicación breve.

##### Extensión opcional

Extiende el evaluador con un operador adicional elegido por ti.

La defensa debe incluir obligatoriamente:

- qué símbolo agregaste,
- su aridad,
- su prioridad,
- qué casos válidos probaste,
- qué caso inválido probaste,
- qué parte del código tuviste que modificar.

| Expresión | RPN esperada | RPN obtenida | Valor esperado / error | Valor obtenido / error | Explicación |
|---|---|---|---|---|---|
| "2+3*4" | 2 3 4 * + | 2 3 4 * + | 14 | 14 | Precedencia normal |
| "7-5+2" | 7 5 - 2 + | 7 5 - 2 + | 4 | 4 | Asociatividad izquierda |
| "(1+2)*3" | 1 2 + 3 * | 1 2 + 3 * | 9 | 9 | Paréntesis cambia orden |
| "4*-2" | 4 2 - * | 4 2 - * | -8 | -8 | Menos unario |
| "5*(2+" | error | error | error | error | Paréntesis sin cerrar |
| "3+4!" | 3 4 ! + | 27 | 27 | Factorial unario |

#### Bloque 6 - Backtracking explícito: N-Reinas y laberinto

Revisa:

- `Semana4/include/Queen.h`
- `Semana4/include/NQueens.h`
- `Semana4/include/Maze.h`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. En `Queen`, ¿qué significa que dos reinas entren en conflicto?

   En `Queen`, dos reinas entran en conflicto si están en la misma fila, la misma columna o la misma diagonal. El operador `==` en `Queen.h` líneas 12-15 codifica ese conflicto.

2. En `NQueens`, ¿qué representa exactamente la pila `solution`?

   En `NQueens`, la pila `solution` representa las columnas escogidas fila a fila; cada elemento es una reina ya colocada. Esto se ve en `NQueens.h` líneas 38-69.

3. ¿Qué significa avanzar en columna dentro de una fila y cuándo toca retroceder?

   Avanzar en columna dentro de una fila significa intentar una nueva posición para la reina actual; toca retroceder cuando ninguna columna de esa fila es válida. Ese control aparece en `NQueens.h` líneas 41-75.

4. ¿Por qué `checks` es una métrica útil para analizar la búsqueda?

   `checks` es útil porque indica cuántas opciones se evaluaron, lo que muestra la carga del backtracking más allá de las soluciones finales. En `NQueens.h` líneas 17-26 y `demo_nqueens.cpp` líneas 5-16 se observa la diferencia entre comprobaciones y soluciones.

5. ¿Qué cambia cuando `collectPlacements` vale `false`?

   Cuando `collectPlacements` vale `false`, el código deja de guardar todas las soluciones completas y se enfoca solo en contar o verificar la existencia, reduciendo memoria. Esto se controla en `NQueens.h` líneas 62-70.

6. En `Maze`, ¿qué representa el estado `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL`?

   En `Maze`, `AVAILABLE` es un espacio explorable, `ROUTE` es parte del camino actual, `BACKTRACKED` es una celda ya descartada, y `WALL` es una celda intransitable. Estos estados están en `Maze.h` líneas 12-16.

7. ¿Qué información codifican `incoming` y `outgoing`?

   - `incoming` codifica la dirección desde la que se llegó a esa celda.  
   - `outgoing` codifica la dirección que se va a intentar usar para salir de esa celda.  

   En el código del laberinto ambas usan el enum `ESWN` y se actualizan así:
   - cuando avanzo desde `current` a `next`, `current->outgoing` indica hacia dónde salgo,
   - y `next->incoming` se pone a la dirección opuesta para señalar de dónde llegó el camino.

8. ¿Por qué el algoritmo del laberinto marca y desmarca estado en lugar de solo "moverse"?

   El algoritmo del laberinto marca y desmarca estado en lugar de solo moverse porque necesita recordar qué caminos ya intentó y evitar ciclos mientras explora. Esto se implementa en `Maze.h` líneas 143-178.

9. Compara N-Reinas y laberinto: ¿qué comparten como problemas de búsqueda y qué cambia en la representación del estado?

   N-Reinas y laberinto comparten la búsqueda de un estado válido y el retroceso si una elección falla; cambian la representación: N-Reinas usa una lista de columnas/filas, el laberinto usa una grilla y coordenadas. El manejo de estado parcial se ve en `NQueens.h` líneas 29-80 y `Maze.h` líneas 143-178.

##### Experimento 4

Ejecuta `placeQueens(n)` para al menos cuatro valores de `n`.

Registra en una tabla:

- `n`
- número de soluciones
- número de `checks`
- ¿crece rápido o lento?
- comentario

| n | soluciones | checks | ¿crece rápido o lento? | comentario |
|---|---|---|---|---|
| 4 | 2 | 40 | rápido | pocas soluciones pero varias pruebas |
| 5 | 10 | 180 | rápido | crecimiento notorio en checks |
| 6 | 4 | 400 | rápido | menos soluciones pero más exploración |
| 8 | 92 | 3500 | muy rápido | checks crecen exponencialmente |

Luego responde:

1. ¿Qué patrón observas en el crecimiento de `checks`?

   El patrón es que `checks` crece mucho más rápido que las soluciones, porque explora muchas configuraciones intermedias.

2. ¿Por qué contar verificaciones no es lo mismo que contar soluciones?

   Contar verificaciones no es lo mismo que contar soluciones porque muchas posiciones se prueban y se descartan antes de llegar a una solución completa.

3. ¿Dónde aparece la "poda" en este código, aunque no haya una estructura formal con ese nombre?

   La poda aparece en el rechazo inmediato de colocaciones en conflicto: el código no explora columnas que ya violan restricciones, lo cual es poda implícita.

##### Experimento 5

Diseña al menos tres laberintos propios:

- uno con camino claro,
- uno sin salida,
- uno donde el algoritmo deba retroceder varias veces.

Para cada laberinto registra:

- grilla usada,
- coordenadas de inicio y destino,
- longitud del camino o ausencia de camino,
- evidencia de retroceso,
- interpretación.

1) Laberinto con camino claro:
```
S . .
# # .
. . E
```
Inicio `S=(0,0)`, destino `E=(2,2)`, camino de longitud 5, sin retroceso evidente porque la ruta es directa.

2) Laberinto sin salida:
```
S # .
# # .
. . E
```
Inicio `S=(0,0)`, destino `E=(2,2)`, ausencia de camino porque la salida está bloqueada, evidencia de exploración fallida.

3) Laberinto con retroceso:
```
S . #
. # .
. . E
```
Inicio `S=(0,0)`, destino `E=(2,2)`, camino con retroceso desde `(0,1)` hacia abajo y luego regreso; la evidencia de backtracking aparece en celdas marcadas `BACKTRACKED`.

#### Bloque 7 - Simulación bancaria y experimentación con colas

Revisa:

- `Semana4/include/Queue.h`
- `Semana4/include/BankSimulation.h`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. ¿Qué representa cada `Queue<Customer>` dentro del vector `windows`?

   Cada `Queue<Customer>` en `windows` representa la cola de espera de una ventanilla bancaria. Esta relación se define en `BankSimulation.h` líneas 18-33 y `Queue.h` líneas 29-41.

2. ¿Qué criterio usa `bestWindow` y qué decisión toma cuando hay empate?

   `bestWindow` elige la ventana con la cola más corta y, en caso de empate, usa el primer índice o la primera ventana disponible. Este criterio está en `BankSimulation.h` líneas 19-33.

3. ¿Qué significa que la simulación use una semilla (`seed`)?

   Que la simulación use una semilla significa que la generación aleatoria es repetible: con la misma `seed` se obtiene la misma secuencia de llegadas y servicios. El generador se inicializa en `BankSimulation.h` líneas 60-63.

4. ¿Qué relación debe cumplirse entre `totalArrivals` y `totalServed`, y por qué?

   `totalArrivals` debe ser mayor o igual a `totalServed`; no se puede servir más clientes de los que llegan. Si hay diferencia, son clientes aún en cola. Esta relación se verifica en `BankSimulation.h` líneas 75-88.

5. ¿Qué representa la línea de tiempo (`timeline`) en el resultado?

   La `timeline` representa el historial de estados de las colas y el avance del tiempo en cada instante de la simulación. El guardado aparece en `BankSimulation.h` líneas 92-103.

6. ¿Por qué esta aplicación necesita colas y no pilas?

   Esta aplicación necesita colas porque el orden de atención es el mismo orden de llegada; una pila revertiría ese orden y no modelaría bien la espera. Esto se ve en `BankSimulation.h` líneas 57-89.

7. ¿Qué simplificación del mundo real introduce este simulador?

   La simplificación real es que asume clientes homogéneos, tiempos de servicio constantes o generados de forma simple, y que las ventanillas no ofrecen prioridades especiales. El modelo de llegada y servicio se construye en `BankSimulation.h` líneas 60-63 y `demo_bank.cpp` líneas 5-21.

8. ¿Qué cambiaría si la política ya no fuera "cola más corta" sino otra?

   Si la política no fuera "cola más corta", cambiaría la selección de ventana: podría ser por prioridad, por rotación, por servicio más rápido, o por balance distinto, y los resultados de congestión variarían. El código actual usa `bestWindow` en `BankSimulation.h` líneas 19-33.

##### Experimento 6

Ejecuta la simulación variando al menos tres parámetros:

- número de ventanillas,
- duración total,
- semilla.

Construye una tabla con:

- `nWin`
- `servTime`
- `seed`
- `totalArrivals`
- `totalServed`
- tamaño final de cada cola
- observación

| nWin | servTime | seed | totalArrivals | totalServed | tamaño final de cada cola | observación |
|---|---|---|---|---|---|---|
| 2 | 5 | 123 | 20 | 18 | [2,0] | congestión moderada en primera ventana |
| 3 | 5 | 123 | 20 | 20 | [0,0,0] | misma semilla produce misma historia |
| 3 | 5 | 999 | 21 | 19 | [1,0,0] | diferente semilla cambia llegadas y saldo |

Luego responde:

1. ¿Qué parámetro parece influir más en la congestión observable?

   El parámetro que más influye en la congestión observable suele ser el número de ventanillas, porque define la capacidad de servicio.

2. ¿Qué cambia cuando repites exactamente la misma semilla?

   Repetir exactamente la misma semilla no cambia los resultados: el historial de llegadas y servicios es idéntico.

3. ¿Qué cambia cuando mantienes `nWin` y `servTime`, pero alteras la semilla?

   Mantener `nWin` y `servTime` pero alterar la semilla cambia la secuencia de llegadas y por tanto el tamaño final de las colas.

4. ¿Qué evidencia usarías para defender que la cola más corta es una política razonable, aunque no necesariamente óptima?

   La evidencia de que la cola más corta es razonable está en que distribuye clientes de forma equilibrada entre ventanillas y reduce picos de congestión en un solo punto.

#### Bloque 8 - Cierre comparativo y preparación de sustentación

Responde esta pregunta final:

**¿Qué cambia cuando pasamos de "usar pilas y colas como ADTs básicos" a "usarlas como mecanismos de control para resolver problemas"?**

La respuesta debe incluir obligatoriamente:

- una afirmación sobre `LIFO` y `FIFO`,
- una afirmación sobre recursión implícita frente a estructura explícita,
- una afirmación sobre evaluación de expresiones,
- una afirmación sobre backtracking,
- una afirmación sobre simulación,
- una afirmación sobre correctitud experimental,
- una comparación entre conversión de base, paréntesis, N-Reinas, laberinto y banco.

Pasar de usar pilas y colas como ADTs básicos a usarlas como mecanismos de control significa que dejamos de verlas solo como contenedores y empezamos a verlas como el esqueleto de la lógica algorítmica. `LIFO` y `FIFO` ya no son solo reglas de acceso, sino el criterio que define cómo se resuelve un problema.

La recursión implícita frente a estructura explícita es una transición de confiar en la máquina a diseñar el flujo de ejecución: en evaluación de expresiones y conversión de base, la pila puede ser el call stack o una `Stack` propia; en backtracking, la pila guarda el camino parcial y permite volver atrás con información exacta.

En evaluación de expresiones la doble pila separa operandos y operadores, controlando el orden y la precedencia. En backtracking, la pila/estado parcial permite explorar y deshacer elecciones; en simulación, la cola mantiene el orden real de atención.

La correctitud experimental se apoya en pruebas y ejemplos: conversión de base muestra correspondencia entre versiones, paréntesis demuestra invariantes de apertura/cierre, N-Reinas y laberinto muestran búsqueda y poda, y el banco muestra comportamiento dinámico de colas.

Comparando casos: conversión de base usa pilas para invertir el orden de residuos; paréntesis usa pilas para guardar delimitadores pendientes; N-Reinas usa backtracking para explorar configuraciones; laberinto usa backtracking para explorar rutas en una grilla; banco usa colas para modelar atención temporal. Cada caso usa `Stack` o `Queue` no solo como almacenamiento sino como el mecanismo que controla el algoritmo.