#include "mersenne_twister.h"

MersenneTwister::MersenneTwister(uint64_t seed) : RandomNumberGenerator(seed), rng(static_cast<unsigned int>(seed)) {}

double MersenneTwister::generate()
{
    return std::generate_canonical<double, 10>(rng);
}
