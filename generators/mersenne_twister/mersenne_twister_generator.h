#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>

class MersenneTwisterGenerator : public RandomNumberGenerator
{
public:
    std::mt19937 gen;

    MersenneTwisterGenerator(int seed);
    void seed(int seed) override;
    double operator()() override;
    void discard(unsigned long long n) override;
    double min() override;
    double max() override;
};
