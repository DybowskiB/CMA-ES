#pragma once

#include "../random_double_number_generator.h"

#include <random>
#include <cstdint>

class Xoroshiro : public RandomDoubleNumberGenerator
{
private:
    uint64_t seed64;
    uint64_t s[4];
    static inline uint64_t rotl(const uint64_t x, int k);
    double next();

public:
    Xoroshiro(int seed);
    void seed(int) override;
    double operator()() override;
    void discard(int) override;
    double min() override;
    double max() override;
};
