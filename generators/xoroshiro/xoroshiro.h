#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>

class Xoroshiro : public RandomNumberGenerator
{
private:
    int counter;
    uint64_t s[4];
    static inline uint64_t rotl(const uint64_t x, int k);
    uint64_t next();
    void check_jump();
    void jump(void);
    void long_jump(void);

public:
    Xoroshiro(uint64_t seed);
    double generate(double a, double b) override;
};
