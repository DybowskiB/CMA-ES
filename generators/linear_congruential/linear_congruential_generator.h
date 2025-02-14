#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>

class LinearCongruentialGenerator : public RandomNumberGenerator
{
public:
    std::minstd_rand gen;

    LinearCongruentialGenerator(int seed);
    
    void seed(int seed) override;
    double operator()() override;
    void discard(unsigned long long n) override;
    double min() override;
    double max() override;
};