#pragma once

#include "../random_number_generator.h"

#include <random>

class MersenneTwister : public RandomNumberGenerator
{
private:
    std::mt19937 rng;

public:
    MersenneTwister(uint64_t);
    double generate(double, double) override;
};
