### Valgrind
Para comprobar errores en manejo de memoria se uso valgrind y para los test de edge_cases no mostró error:

```bash
valgrind ./build/edge_cases
```

==2406770== Memcheck, a memory error detector
==2406770== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==2406770== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==2406770== Command: ./build/edge_cases
==2406770== 
Casos borde finalizados
==2406770== 
==2406770== HEAP SUMMARY:
==2406770==     in use at exit: 0 bytes in 0 blocks
==2406770==   total heap usage: 88 allocs, 88 frees, 24,852,148 bytes allocated
==2406770== 
==2406770== All heap blocks were freed -- no leaks are possible
==2406770== 
==2406770== For lists of detected and suppressed errors, rerun with: -s
==2406770== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
