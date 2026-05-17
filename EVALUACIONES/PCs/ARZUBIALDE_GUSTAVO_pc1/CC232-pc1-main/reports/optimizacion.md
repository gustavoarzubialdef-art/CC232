### El resultado del benchmark es el siguiente:

=== Benchmark (n = 10000000) ===

Metodo              Tiempo (ms)    Operaciones         
-------------------------------------------------------
STL                 129            124434633           
countOnes1          817            124434633           
Optimizado          299            10000000            

Se puede observar que la optimización propia es mejor que el método ingenuo, sin 
embargo no llega a superar a la librería STL, pese a que esta ejecuta muchos más bucles.
