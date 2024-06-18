#pragma once

#include <vector>
#include <cstdint>

// Abstract class for random double number generator
class RandomNumberGenerator
{
public:
    using result_type = double;

    int seed_val;

    RandomNumberGenerator(int);
    double transform_to_range(double, double, double);
    virtual void seed(int) = 0;
    virtual double operator()() = 0;
    virtual void discard(unsigned long long) = 0;
    virtual double min() = 0;
    virtual double max() = 0;
    virtual ~RandomNumberGenerator() = default;
};
