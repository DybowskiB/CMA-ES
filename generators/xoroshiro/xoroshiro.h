#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>
#include <climits>

class Xoroshiro : public RandomNumberGenerator
{
private:
    const double MIN_VAL = 0.0;
    const double MAX_VAL = static_cast<double>(INT_MAX);

    uint64_t seed64;
    uint64_t s[4];
    static inline uint64_t rotl(const uint64_t x, int k);
    double next();

public:
    Xoroshiro(int seed);
    void seed(int) override;
    double operator()() override;
    void discard(unsigned long long) override;
    double min() override;
    double max() override;
};
