#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>

class XoroshiroGenerator : public RandomNumberGenerator
{
public:
    XoroshiroGenerator(int seed);
    void seed(int seed) override;
    double operator()() override;
    void discard(unsigned long long n) override;
    double min() override;
    double max() override;

private:
    uint64_t seed64;
    uint64_t s[4];
    static inline uint64_t rotl(const uint64_t x, int k);
    double next();
};
