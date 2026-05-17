#include "loop_counter.h"

LoopCounter::LoopCounter() : count(0) {}

void LoopCounter::reset() {
    count = 0;
}

void LoopCounter::increment(unsigned long long n) {
    count += n;
}

unsigned long long LoopCounter::get() const {
    return count;
}
