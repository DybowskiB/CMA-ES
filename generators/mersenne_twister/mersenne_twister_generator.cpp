#include "mersenne_twister_generator.h"

#include <stdint.h>
#include <iostream>

MersenneTwisterGenerator::MersenneTwisterGenerator(int seed)
    : RandomNumberGenerator(seed, "MersenneTwister"), gen(seed) {}

void MersenneTwisterGenerator::seed(int s)
{
    seed_val = s;
    gen.seed(s);
}

double MersenneTwisterGenerator::operator()()
{
    return static_cast<double>(gen());
}

void MersenneTwisterGenerator::discard(unsigned long long n)
{
	gen.discard(n);
}

double MersenneTwisterGenerator::min()
{
    return static_cast<double>(gen.min());
}

double MersenneTwisterGenerator::max()
{
    return static_cast<double>(gen.max());
}
