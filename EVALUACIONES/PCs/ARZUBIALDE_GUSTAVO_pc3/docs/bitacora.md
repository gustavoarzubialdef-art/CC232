# Bitácora de desarrollo — PC3 CC232 · Codeforces 702F T-Shirts

## 6 de junio de 2026

- Se revisó `Practica3_CC232/Indicaciones.md` y se identificaron los entregables
  obligatorios: README, CMake, pruebas, resultados, respuestas, bitácora y demo.
- Se confirmó el problema asignado: Codeforces 702F - T-Shirts.
- Se analizó la restricción: hasta `2×10⁵` camisetas y `2×10⁵` compradores;
  una simulación `O(nk)` llega a `4×10¹⁰` operaciones, inviable en 4 segundos.
- Se eligió Treap aumentado como estructura principal por su relación directa
  con BST de Semana 5 (propiedad de orden por `(money, id)`) y Treap de
  Semana 6 (prioridades aleatorias para altura esperada `O(log k)`).

## 7 de junio de 2026

- Se modeló la simulación ingenua: ordenar camisetas por calidad descendente
  (precio ascendente en empates) y recorrer cada presupuesto contra todas las
  camisetas. Se implementó `solveNaive` como oráculo de corrección.
- Se diseñó la inversión del algoritmo: iterar sobre camisetas y actualizar en
  bloque a todos los compradores elegibles usando `splitLessThan` y `addLazy`.
- Se esbozó la estructura `CustomerNode` con campos `money`, `id`, `bought`,
  `lazyMoney`, `lazyBought` y `priority`.

## 8 de junio de 2026 — primer commit

Archivos subidos: `CMakeLists.txt` (versión inicial, solo target `tshirts`),
`include/tshirts_solver.h`, `src/main.cpp`, `src/tshirts_solver.cpp`.

- Se implementó `CustomerTreap` completo: `splitLessThan`, `merge`, `insert`,
  `addLazy`, `collectAndInsert` y `push`.
- Se agregó `checkInvariant` y `assertInvariantIfSmall`: verifican el orden
  inorder por `(money, id)` automáticamente cuando `k ≤ 256`, sin penalizar
  los casos máximos.
- Se implementó `solveFast` conectando `build`, el bucle de camisetas y
  `buyForEligible`, y `solveNaive` como referencia de corrección.
- Se definió la API pública en `tshirts_solver.h`: `solveFast`, `solveNaive`,
  `verifyAgainstNaive` y `printOrderedTrace`.
- Se configuró `CMakeLists.txt` con `tshirts_core`, el ejecutable `tshirts` y
  `enable_testing()`. Solo incluye el binario principal en esta versión.

## 9 de junio de 2026 — segundo commit

Archivos subidos: `CMakeLists.txt` actualizado (targets `test_tshirts`,
`demo_trace`, `demo_samples`), `demos/demo_trace.cpp`, `demos/demo_samples.cpp`,
`tests/test_tshirts.cpp`, `resultados/casos_borde.txt`,
`resultados/ejecucion_pc3.txt`, `resultados/tests_pc3.txt`.

- Se extendió `CMakeLists.txt` con tres targets nuevos registrados en `ctest`.
- Se agregó `demo_trace.cpp`: muestra el estado inorder del Treap
  (`id`, `money`, `bought`) después de procesar cada camiseta.
- Se agregó `demo_samples.cpp`: corre los dos ejemplos oficiales del enunciado
  con datos hardcodeados, sin pedir entrada interactiva.
- Se agregaron pruebas en `test_tshirts.cpp`: casos públicos del enunciado,
  caso mínimo, empates por calidad, frontera de compra (`boundaryWithCrossingCustomers`),
  comparación explícita contra `solveNaive` y 200 casos aleatorios pequeños
  contra fuerza bruta (`smallRandomAgainstNaive`).
- Se subió evidencia textual en `resultados/`: salida de `ctest`, ejecución
  del binario principal y descripción de casos borde.
- Se verificó que `ctest --test-dir build --output-on-failure` pasa en verde
  desde MSYS2 UCRT64.

## 10 de junio de 2026 — tercer commit (miércoles)

Archivos subidos: `docs/bitacora.md`, `docs/respuestas_obligatorias.md`.

- Se redactó la bitácora con el avance real día a día.
- Se completaron las 20 preguntas comunes de defensa oral y las 3 preguntas
  específicas del problema en `respuestas_obligatorias.md`.

## 11 de junio de 2026 — cuarto commit (jueves)

Archivos y cambios incluidos: `.gitignore`, correcciones finales en cabeceras, benchmark y ajustes en CMake.

- Se agrega `.gitignore` para excluir `build/`, ejecutables, objetos y archivos generados por CMake.
- Se verifica que `git ls-files` no muestre ningún `.exe`, `.o`, `CMakeCache.txt` ni carpeta `build/`.
- Se revisa que `cmake -S . -B build && cmake --build build` funcione en limpio desde cero en MSYS2 UCRT64.
- **Cabecera `tshirts_solver.h`**: se eliminan librerías innecesarias, quedando solo:
  ```cpp
  #pragma once
  #include <iosfwd>
  #include <vector>
  ```