#pragma once

class LoopCounter {
private:
    unsigned long long count;

public:
    LoopCounter();
    void reset();
    void increment(unsigned long long n = 1);
    unsigned long long get() const;
};
