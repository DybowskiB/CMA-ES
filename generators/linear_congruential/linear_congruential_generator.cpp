#include "linear_congruential_generator.h"

LinearCongruentialGenerator::LinearCongruentialGenerator(uint64_t seed) : RandomNumberGenerator(seed), rng(static_cast<unsigned int>(seed)) {}

double LinearCongruentialGenerator::generate(double a, double b)
{
    std::uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}