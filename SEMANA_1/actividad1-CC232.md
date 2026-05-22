## Actividad 1- CC232

### Integrantes
- Gustavo Anthony Arzubialde Fierro 20230205H
- Victor Hugo Cadillo Gutierrez


#### Bloque 1

1. Expliquen con sus palabras la diferencia entre **problema**, **algoritmo**, **ADT** e **implementación**.
- PROBLEMA: Describe una necesidad o situación sin decir cómo resolverla.
- ALGORITMO: Es el **método o conjunto de pasos** para resolver el problema.
- ADT (ABSTRACT DATA TYPE): El ADT es la idea o el modelo de una estructura de datos, también lo puedes ver como una “caja negra”: sabes qué hace, pero no cómo lo hace.
- IMPLEMENTACION: La implementación es cómo construyes esa “caja negra” en la realidad.

---

2. En `bubble_sort.cpp`, expliquen qué observable conecta correctitud y costo.
Por eso, los swaps son un observable que está en la intersección:
- Si hay cero swaps, el arreglo ya estaba ordenado (correctitud alcanzada sin costo adicional).
- Si hay muchos swaps, el arreglo estaba muy desordenado y el costo de corregirlo fue alto.

---

3. En `power.cpp`, expliquen por qué `power` mejora la idea de una versión ingenua.
- Versión ingenua (powerBF):
Multiplica a por sí mismo n veces en un bucle lineal.
- Complejidad: O(n).
- Si n es muy grande, el número de operaciones crece proporcionalmente y se vuelve lento.
- Versión mejorada (power):
Utiliza la técnica de exponenciación rápida o exponentiation by squaring.
- La idea es que en lugar de multiplicar a repetidamente, se aprovecha la descomposición binaria del exponente n.
- Cada vez que n es par, se reduce a calcular a^{n/2} y luego elevarlo al cuadrado.
- Cuando n es impar, se multiplica una vez más por a y se sigue reduciendo.
- Complejidad: O(\log n).

---

4. En `fibonacci.cpp`, expliquen por qué una función puede ser correcta y aun así ser una mala elección práctica.
Una función puede ser correcta matemáticamente (produce el resultado esperado) pero ser una mala elección práctica si su rendimiento es deficiente, consume demasiados recursos o es difícil de mantener. En este caso, la versión recursiva ingenua (fib(n)) es correcta pero impráctica, mientras que la iterativa (fibI) y la recursiva optimizada (fib(n, prev)) son mucho más adecuadas en aplicaciones reales.

---

5. En `count_ones.cpp`, expliquen por qué el tamaño de entrada no siempre coincide con el valor numérico.
El valor numérico (ej. 7 vs 8) no determina directamente el costo computacional de contar unos.
- En countOnes1, el costo depende de cuántos bits estén en 1, no de cuán grande sea el número.
- En countOnes2, el costo es fijo porque se procesan todos los bits en paralelo con operaciones de máscara.
Por eso se dice que el tamaño de entrada (cantidad de bits relevantes para el algoritmo) no siempre coincide con el valor numérico del entero.

---

6. En `demo_adt_secuencia.cpp`, expliquen por qué la misma interfaz puede convivir con representaciones distintas.

La misma interfaz puede convivir con representaciones distintas porque lo que importa para el cliente es qué operaciones están disponibles y qué garantizan, no cómo se 
implementan. Esto es la esencia de un ADT: una especificación abstracta con múltiples posibles realizaciones.

#### Bloque 2

1. En `demo_bubblesort.cpp`, ¿qué salida sirve para defender costo y no solo resultado?

La salida que sirve para defender costo es la que reporta estadísticas de ejecución (comparaciones, intercambios, último swap), porque permite analizar la eficiencia del 
algoritmo, no solo confirmar que el resultado está correcto.

---

2. En `demo_power.cpp`, ¿qué comparación concreta muestra una mejora algorítmica?

La salida que compara powerBF vs power es la evidencia clara de mejora algorítmica: mismo resultado, pero distinto costo.

---

3. En `demo_fibonacci.cpp`, ¿qué crecimiento se vuelve defendible?

El crecimiento que se vuelve defendible es el lineal o mejor (constante por paso), porque escala razonablemente con n. El crecimiento exponencial de la versión recursiva ingenua 
no se puede justificar más allá de fines didácticos.

---

4. En `demo_countones.cpp`, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?

ejemplos como 7 vs 8 o el 361 del código son los que mejor distinguen entre el valor decimal y el tamaño en bits, porque muestran que un número más grande puede tener 
menos unos, y por tanto menor costo en el algoritmo que elimina bits uno por uno.

#### Bloque 3

1. ¿Qué funciones o ideas están verificando las pruebas públicas?

Las pruebas públicas están verificando ideas clave de algoritmos:
- Equivalencia entre versiones ingenuas y optimizadas.
- Correcta aplicación de invariantes (arreglo ordenado, número de movimientos, conteo de bits).
- Que el costo algorítmico se pueda defender (comparaciones en bubble sort, eficiencia en potencias, crecimiento lineal vs exponencial en Fibonacci).

---

2. ¿Qué sí demuestra una prueba pública?

Qué sí demuestra
- Corrección funcional en casos concretos: que la función devuelve el resultado esperado para ciertos valores de entrada.
- Equivalencia entre implementaciones: que distintas versiones (iterativa, recursiva, optimizada) producen el mismo resultado.
- Cumplimiento de invariantes observables: por ejemplo, que un arreglo queda ordenado, que el número de movimientos de Hanoi coincide con la fórmula, que el conteo de bits es correcto.
- Ejemplos representativos: muestran que el algoritmo funciona en situaciones típicas o ilustrativas (caso vacío, caso pequeño, caso con desorden, etc.).

---

3. ¿Qué no demuestra una prueba pública?

Qué no demuestra
- Corrección general para todos los posibles casos: probar con unos pocos valores no garantiza que el algoritmo funcione siempre.
- Eficiencia algorítmica en el peor caso: aunque se midan comparaciones o swaps, una prueba pública no certifica la complejidad asintótica.
- Robustez frente a entradas extremas: no asegura que funcione con números muy grandes, arreglos enormes o condiciones límite.
- Ausencia de errores ocultos: un assert puede pasar en los casos probados y aún así fallar en otros no contemplados.
- Calidad del diseño interno: no evalúa si el código es mantenible, claro o escalable, solo que produce el resultado correcto en ese escenario.

---
4. Elijan **una** pregunta de `preguntas_semana1.md` y respóndanla bien.
¿Qué es un algoritmo y qué condiciones debe cumplir para ser considerado correcto y útil?
Un algoritmo es un conjunto finito y ordenado de pasos o instrucciones que permiten resolver un problema o realizar una tarea de manera sistemática.
Condiciones para que un algoritmo sea correcto y útil
Corrección
- Produce la salida esperada: para cada entrada válida, el algoritmo debe devolver el resultado correcto según la especificación del problema.
- Termina en un número finito de pasos: no puede quedar en un bucle infinito (salvo que el problema lo requiera explícitamente, como en sistemas interactivos).
- Maneja casos límite: entradas vacías, valores extremos o condiciones especiales deben estar contempladas.
Utilidad (eficiencia y aplicabilidad)
- Eficiencia temporal: el número de operaciones debe crecer de manera defendible (idealmente polinómica o mejor) respecto al tamaño de la entrada.
- Eficiencia espacial: el uso de memoria debe ser razonable y proporcional al problema.
- Claridad y mantenibilidad: debe ser comprensible y posible de implementar sin ambigüedades.
- Generalidad: debe funcionar para todas las entradas dentro del dominio definido, no solo para ejemplos específicos.
- Escalabilidad: debe poder aplicarse a problemas grandes sin volverse impráctico.

#### Bloque 4

1. ¿Qué diferencia observable deja `demo_const_refs.cpp` entre lectura, modificación y copia?

- Lectura → no cambia nada.
- Modificación en el lugar → altera el objeto original.
- Copia → preserva el original y devuelve un nuevo objeto con cambios.

---

2. En `bench_vector_growth.cpp`, ¿qué cambia con `reserve`?

Lo que cambia con reserve es el costo de crecimiento del vector. El resultado final (tener los mismos elementos) es idéntico, pero el camino para llegar allí es más eficiente: 
menos realocaciones, menos copias y mejor rendimiento.

---

3. En `bench_vector_ops.cpp`, ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?

No cuestan lo mismo porque el vector garantiza memoria contigua. Insertar al final no requiere mover nada, insertar al inicio obliga a moverlo todo, e insertar en el medio mueve solo una parte. El benchmark refleja estas diferencias de complejidad: constante vs lineal completa vs lineal parcial.

---

4. En `bench_cache_effects.cpp`, ¿qué intuición deja sobre localidad de memoria?

La localidad de memoria importa tanto como la cantidad de operaciones. Un algoritmo que accede secuencialmente a datos contiguos puede ser mucho más rápido que otro que hace accesos aleatorios o sigue punteros, aunque ambos hagan el mismo número de sumas.
En otras palabras: no basta contar operaciones, hay que considerar cómo se accede a la memoria y cómo la caché de la CPU las aprovecha.

#### Bloque 5

1. Según `Ejercicios0.md`, ¿cuál es el orden correcto antes de optimizar?

Elegir bien el algoritmo → Verificar la correctitud del programa → Medir rendimiento → Explorar optimizaciones del compilador.

---

2. ¿Qué quiere mostrar `stl_optimizacion_demostracion.cpp` con `reserve`, `nth_element`, `partial_sort` y `lower_bound`?

En conjunto, el programa quiere transmitir que optimizar no es solo micro‑optimizar, sino elegir el algoritmo y la estructura de datos adecuados. La STL ofrece herramientas 
muy potentes que, usadas correctamente, permiten resolver problemas con mayor eficiencia y claridad

---

3. ¿Qué tipo de evidencia puede producir `resolver_ejercicios0_v4.2.sh`?

La evidencia que produce es principalmente:
- Datos medibles (tiempo, tamaño, cobertura).
- Pruebas de correctitud (salida esperada vs. real).
- Diagnósticos de herramientas (sanitizers, gcov, gprof).
- Documentación automática en un reporte Markdown que integra todo lo anterior.
Es decir, el script no solo ejecuta los experimentos, sino que deja un rastro verificable que permite comparar configuraciones, detectar problemas y justificar conclusiones.
¿Quieres que te muestre un ejemplo de cómo se vería un fragmento del reporte final con una tabla y un extracto de salida, para visualizar mejor la evidencia que produce?

---

4. ¿Qué limitaciones de entorno menciona `INSTRUCCIONES_Ejercicios0_v4.2.md`?

El documento advierte que algunos experimentos avanzados (sanitizers, cobertura, profiling) pueden no funcionar bien en Windows/MSYS2, y recomienda usar WSL o Linux para obtener resultados completos y confiables.

---

5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?


#### Bloque 6

¿Qué cambia cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental?
La respuesta debe incluir obligatoriamente:

* una afirmación de especificación,
* una afirmación de correctitud,
* una afirmación de costo,
* una afirmación de representación o memoria,
* una advertencia metodológica.