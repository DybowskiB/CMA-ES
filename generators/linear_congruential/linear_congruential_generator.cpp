/*#include "linear_congruential_generator.h"

LinearCongruentialGenerator::LinearCongruentialGenerator(int seed) : RandomNumberGenerator(seed), rng(static_cast<unsigned int>(seed)) {}

double LinearCongruentialGenerator::operator()()
{
    return rng();
}

void LinearCongruentialGenerator::discard(int n)
{
    rng.discard(n);
}

constexpr unsigned LinearCongruentialGenerator::min()
{
    return 
}

constexpr unsigned LinearCongruentialGenerator::max()
{
    return static_cast<unsigned>(5);
}*/