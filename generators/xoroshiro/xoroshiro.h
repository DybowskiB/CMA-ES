#pragma once

#include <random>
#include <cstdint>
#include "../random_number_generator.h"

class Xoroshiro : public RandomNumberGenerator
{
private:
    uint64_t s[4];
    static inline uint64_t rotl(const uint64_t x, int k);
    uint64_t next();

public:
    Xoroshiro(uint64_t seed);
    double generate() override;
};
