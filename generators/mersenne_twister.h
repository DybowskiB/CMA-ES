#ifndef MERSENNE_TWISTER_H
#define MERSENNE_TWISTER_H

#include "random_number_generator.h"
#include <random>

class MersenneTwister : public RandomNumberGenerator {
private:
    std::mt19937 rng;

public:
    MersenneTwister(int seed);
    double generate() override;
};

#endif