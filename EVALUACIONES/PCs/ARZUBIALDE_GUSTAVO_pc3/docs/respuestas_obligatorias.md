# Respuestas obligatorias — PC3 CC232 · Codeforces 702F T-Shirts

## Preguntas comunes obligatorias

1. **¿Cuál es el problema exacto asignado?**  
   
   El problema asignado es *Codeforces 702F - T-Shirts*.

2. **¿Qué recibe la entrada y qué produce la salida?**  
   
   La entrada recibe `n`, luego `n` pares `(c_i, q_i)` de precio y calidad, después `k` y los presupuestos `b_j`. La salida son `k` enteros: cuántas camisetas compra cada comprador siguiendo la estrategia del enunciado.

3. **¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**  
   
   La restricción que vuelve insuficiente es que `n` y `k` pueden llegar hasta `2 * 10^5`. Simular cada comprador contra cada camiseta implicaría hasta `4 * 10^10` operaciones, lo cual es imposible en 4 segundos.

4. **¿Cuál sería la solución ingenua y cuál es su complejidad?**  
   
   La solución ingenua sería ordenar las camisetas y, para cada comprador, recorrerlas todas restando si alcanza. Eso está implementado en `solveNaive` y cuesta `O(nk)` tiempo y `O(n + k)` espacio.

5. **¿Qué estructura de datos elegiste?**  
   
   Elegí un Treap no rotativo aumentado, ordenado por dinero restante e identificador. Permite partir por precio, aplicar marcas lazy y reinsertar nodos que pierden su posición.

6. **¿Qué estructura de la librería `cc232` se parece más?**  
   
   Se parece a `Libreria_cc232/Semana6/include/Treap.h`, que también usa la propiedad de BST de Semana 5 y la prioridad aleatoria de Semana 6.

7. **¿Qué operación domina el tiempo?**  
   
   La operación que más domina es `CustomerTreap::buyForEligible`, porque por cada camiseta ejecuta particiones, actualizaciones lazy, merges y posibles reinserciones.

8. **¿Qué invariante mantiene tu estructura?**  
   
   El inorder del Treap está ordenado por `(money, id)`, y cada nodo almacena correctamente el dinero restante y las compras acumuladas del comprador, incluyendo lazy pendiente.

9. **¿Dónde se actualiza ese invariante en el código?**  
   
   Se actualiza en `splitLessThan`, `merge`, `insert`, `collectAndInsert` y `addLazy`. Después de `build` y de cada `buyForEligible`, `assertInvariantIfSmall` revisa el invariante en casos pequeños.

10. **¿Qué caso borde puede romper una solución superficial?**  
   
    Un caso borde es cuando un comprador con dinero en `[c, 2c)` compra una camiseta de precio `c`. Su dinero baja a `[0, c)`, y si no se reinserta, el orden del Treap se rompe.

11. **¿Cómo manejas duplicados, empates o elementos obsoletos?**  
    
    Los empates de calidad se resuelven ordenando por menor precio. Los compradores con igual dinero se distinguen por `id`. No hay elementos obsoletos porque las marcas lazy se empujan con `push`.

12. **¿Cuál es la complejidad temporal por operación?**  
    
    Cada `split`, `merge` e `insert` cuesta `O(log k)` esperado. `addLazy` es `O(1)` por subárbol.

13. **¿Cuál es la complejidad total?**  
    
    La complejidad total es `O((n + k) log k)` esperada/amortizada. La parte amortizada viene de reinsertar solo compradores que cruzan de `[c, 2c)` a `[0, c)`.

14. **¿Cuál es la complejidad espacial?**  
    
    Es `O(n + k)`: lista de camisetas ordenada, nodos de compradores y vector de respuestas.

15. **¿Qué parte del código sería más fácil de romper?**  
    
    La separación de tres rangos en `buyForEligible`: menores que `c`, entre `c` y `2c - 1`, y al menos `c` después de restar. Un error ahí desordena el Treap.

16. **¿Qué alternativa de estructura existe y qué perderías con ella?**  
    
    Podría usarse `std::multiset` y actualizar compradores individualmente, pero se perderían las actualizaciones lazy y sería más fácil caer en `O(nk)`.

17. **¿Qué prueba propia escribiste?**  
    
    Escribí `boundaryWithCrossingCustomers` para validar compradores que cambian de frontera, además de `explicitNaiveComparison` y `smallRandomAgainstNaive`.

18. **¿Qué cambiaste durante el bloque sin cortes?**  
    
    Agregué o mostré `smallRandomAgainstNaive`, que genera casos pequeños y compara `solveFast` contra `solveNaive`.

19. **¿Cómo sabes que el cambio no rompió la solución?**  
    
    Porque `ctest` ejecuta casos públicos, casos borde, comparaciones ingenuas y 200 casos aleatorios pequeños. Además, `checkInvariant` verifica el orden del Treap.

20. **¿Qué demuestra que no es una solución de caja negra?**  
    
    El código expone la estructura central: `splitLessThan`, `merge`, `insert`, `addLazy`, `collectAndInsert` y `checkInvariant`. La versión ingenua existe solo como oráculo de pruebas.

---

## Preguntas específicas - Codeforces 702F

1. **¿Qué se ordena primero y por qué ese orden evita recomputar desde cero?**  
   
   Se ordenan camisetas por calidad descendente y precio ascendente en `sortedShirts`. Ese orden es fijo para todos los compradores, por eso cada camiseta se procesa una sola vez.

2. **¿Qué información debe mantener la estructura ordenada?**  
   
   Cada nodo mantiene `money`, `id`, `bought`, punteros del Treap, prioridad aleatoria y marcas lazy (`lazyMoney`, `lazyBought`). Con eso se puede buscar compradores y devolver la respuesta final.

3. **¿Qué parte de la solución depende de búsquedas, particiones o rangos?**  
   
   La función `buyForEligible` parte el Treap en compradores con dinero menor que el precio y compradores con dinero suficiente. Luego resta el precio al rango elegible, vuelve a partir por frontera y reinserta los nodos que ya no pertenecen al mismo rango.

---

## Retos elegidos

### Reto transversal 1 — comparación contra versión ingenua

`verifyAgainstNaive` compara `solveFast` contra `solveNaive` en casos
deterministas. La prueba `explicitNaiveComparison` valida esto en el código.

### Reto transversal 2 — prueba aleatoria pequeña

`smallRandomAgainstNaive` genera 200 instancias aleatorias con parámetros
pequeños y verifica que ambas soluciones coincidan en todas ellas.

### Reto específico del problema

`demo_trace` imprime el estado inorder del Treap (`id`, `money`, `bought`)
después de cada camiseta procesada, mostrando la evolución interna de la
estructura durante la simulación.