### LA SALIDA DEL EJECUTABLE ./observaciones da lo siguiente:

Tiempo de ejecutable con build de depuracion en segundos.
Prueba privada terminada
1.540
Tamaño del ejecutable en KB.
128K    ./build_with_flags/test_depuracion
Tiempo de ejecutable con build de depuracion optimizado en segundos.
Prueba privada terminada
0.503
Tamaño del ejecutable en KB.
124K    ./build_with_flags/test_optimizado
Tiempo de ejecutable con build release en segundos.
Prueba privada terminada
0.401
Tamaño del ejecutable en KB.
128K    ./build_with_flags/test_release
Tiempo de ejecutable con build compacto en segundos.
Prueba privada terminada
0.454
Tamaño del ejecutable en KB.
120K    ./build_with_flags/test_compacto
Tiempo de ejecutable con build -O1 en segundos.
Prueba privada terminada
0.488
Tamaño del ejecutable en KB.
128K    ./build_with_flags/test_O1
Tiempo de ejecutable con build -O3 compacto en segundos.
Prueba privada terminada
0.498
Tamaño del ejecutable en KB.
136K    ./build_with_flags/test_O3

### Se puede observar que los tamaños de los archivos son consistentes, pero el tiempo de ejecución varía, como es
esperable demora mas en depuración y es más rápido en release y con las flags de optimización -O aunque no por mucho.

