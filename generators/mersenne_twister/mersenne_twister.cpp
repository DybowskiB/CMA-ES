#include "mersenne_twister.h"

#include <stdint.h>
#include <iostream>

MersenneTwister::MersenneTwister(int seed) : RandomNumberGenerator(seed), gen(seed) {}

void MersenneTwister::seed(int s)
{
    seed_val = s;
    gen.seed(s);
}

double MersenneTwister::operator()()
{
    return static_cast<double>(gen());
}

void MersenneTwister::discard(unsigned long long n)
{
	gen.discard(n);
}

double MersenneTwister::min()
{
    return static_cast<double>(gen.min());
}

double MersenneTwister::max()
{
    return static_cast<double>(gen.max());
}
