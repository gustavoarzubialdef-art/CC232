TIMEFORMAT=%R
echo "Tiempo de ejecutable con build de depuracion en segundos."
time ./build_with_flags/test_depuracion
echo "Tamaño del ejecutable en KB".
du -sh ./build_with_flags/test_depuracion --block-size=K

echo "Tiempo de ejecutable con build de depuracion optimizado en segundos."
time ./build_with_flags/test_optimizado
echo "Tamaño del ejecutable en KB".
du -sh ./build_with_flags/test_optimizado --block-size=K

echo "Tiempo de ejecutable con build release en segundos."
time ./build_with_flags/test_release
echo "Tamaño del ejecutable en KB".
du -sh ./build_with_flags/test_release --block-size=K

echo "Tiempo de ejecutable con build compacto en segundos."
time ./build_with_flags/test_compacto
echo "Tamaño del ejecutable en KB".
du -sh ./build_with_flags/test_compacto --block-size=K

echo "Tiempo de ejecutable con build -O1 en segundos."
time ./build_with_flags/test_O1
echo "Tamaño del ejecutable en KB".
du -sh ./build_with_flags/test_O1 --block-size=K

echo "Tiempo de ejecutable con build -O3 compacto en segundos."
time ./build_with_flags/test_O3
echo "Tamaño del ejecutable en KB".
du -sh ./build_with_flags/test_O3 --block-size=K
