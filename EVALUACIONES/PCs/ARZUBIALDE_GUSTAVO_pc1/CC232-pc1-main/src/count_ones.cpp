#include "count_ones.h"
#include "loop_counter.h"

int countOnes1(unsigned int n, LoopCounter& counter) {
    int ones = 0;

    while (n > 0) {
        counter.increment(); 
        ++ones;
        n &= (n - 1);
    }

    return ones;
}

