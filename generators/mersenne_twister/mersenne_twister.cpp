#include "mersenne_twister.h"

MersenneTwister::MersenneTwister(uint64_t seed) : RandomNumberGenerator(seed), rng(static_cast<unsigned int>(seed)) {}

double MersenneTwister::generate(double a, double b)
{
    std::uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}
