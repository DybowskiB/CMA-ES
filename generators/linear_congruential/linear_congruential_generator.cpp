#include "linear_congruential_generator.h"

LinearCongruentialGenerator::LinearCongruentialGenerator(uint64_t seed) : RandomNumberGenerator(seed), rng(static_cast<unsigned int>(seed)) {}

double LinearCongruentialGenerator::generate()
{
    return static_cast<double>(rng()) / rng.max();
}