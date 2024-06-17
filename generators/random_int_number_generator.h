#pragma once

#include <vector>
#include <cstdint>

// Abstract class for random int number generator
class RandomIntNumberGenerator
{
public:
    using result_type = int;
    
    int seed_val;

    RandomIntNumberGenerator(int);
    virtual void seed(int) = 0;
    virtual int operator()() = 0;
    virtual void discard(int) = 0;
    virtual int min();
    virtual int max();
    virtual ~RandomIntNumberGenerator() = default;
};
