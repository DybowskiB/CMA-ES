#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>

class MersenneTwister : public RandomNumberGenerator
{
public:
    std::mt19937 gen;

    MersenneTwister(int seed);
    void seed(int) override;
    double operator()() override;
    void discard(unsigned long long) override;
    double min() override;
    double max() override;
};
