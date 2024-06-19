#pragma once

#include <vector>
#include <cstdint>
#include <climits>
#include <string>

// Abstract class for random double number generator
class RandomNumberGenerator
{
protected:
    const double MIN_VAL = 0.0;
    const double MAX_VAL = static_cast<double>(INT_MAX); 

public:
    using result_type = double;

    int seed_val;
    std::string name;

    RandomNumberGenerator(int seed, std::string name);

    double transform_to_range(double, double, double);
    std::string to_string();

    virtual void seed(int) = 0;
    virtual double operator()() = 0;
    virtual void discard(unsigned long long) = 0;
    virtual double min() = 0;
    virtual double max() = 0;
    virtual ~RandomNumberGenerator() = default;
};
