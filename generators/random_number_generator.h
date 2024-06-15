#pragma once

#include <vector>
#include <cstdint>

// Abstract class for random number generator
class RandomNumberGenerator
{
public:
    uint64_t seed;
    RandomNumberGenerator(uint64_t seed) : seed(seed) {}
    virtual double generate() = 0;
    virtual ~RandomNumberGenerator() {}
};
