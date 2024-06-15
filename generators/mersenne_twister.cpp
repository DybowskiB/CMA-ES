#include "mersenne_twister.h"

MersenneTwister::MersenneTwister(int seed) : RandomNumberGenerator(seed), rng(seed) {}

double MersenneTwister::generate()
{
    return std::generate_canonical<double, 10>(rng);
}
