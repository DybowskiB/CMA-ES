#pragma once

#include "../random_int_number_generator.h"

#include <random>
#include <cstdint>

class IntXoroshiro : public RandomIntNumberGenerator
{
private:
    uint64_t seed64;
    uint64_t s[4];
    static inline uint64_t rotl(const uint64_t x, int k);
    double next();

public:    
    IntXoroshiro(int seed);
    void seed(int) override;
    int operator()() override;
    void discard(int) override;
    int min() override;
    int max() override;
};
