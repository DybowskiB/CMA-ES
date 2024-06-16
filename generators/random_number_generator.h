#pragma once

#include <vector>
#include <cstdint>

// Abstract class for random number generator
class RandomNumberGenerator
{
protected:
    double transform_to_range(double rand, double a, double b);
public:
    uint64_t seed;
    RandomNumberGenerator(uint64_t);
    virtual double generate(double, double) = 0;
    virtual ~RandomNumberGenerator() {}
};
