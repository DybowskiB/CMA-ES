#pragma once

#include <vector>
#include <cstdint>

// Abstract class for random double number generator
class RandomDoubleNumberGenerator
{
public:
    using result_type = double;

    int seed_val;

    RandomDoubleNumberGenerator(int);
    virtual void seed(int) = 0;
    virtual double operator()() = 0;
    virtual void discard(int) = 0;
    virtual double min();
    virtual double max();
    virtual ~RandomDoubleNumberGenerator() = default;
};
