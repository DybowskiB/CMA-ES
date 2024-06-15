#pragma once

#include "../random_number_generator.h"
#include <random>

class LinearCongruentialGenerator : public RandomNumberGenerator
{
private:
    std::minstd_rand rng;

public:
    LinearCongruentialGenerator(uint64_t seed);
    double generate() override;
};