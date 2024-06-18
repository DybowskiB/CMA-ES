#include "linear_congruential_generator.h"

#include <stdint.h>
#include <iostream>

LinearCongruentialGenerator::LinearCongruentialGenerator(int seed)
    : RandomNumberGenerator(seed), gen(seed) {}

void LinearCongruentialGenerator::seed(int s)
{
    seed_val = s;
    gen.seed(s);
}

double LinearCongruentialGenerator::operator()()
{
    return static_cast<double>(gen());
}

void LinearCongruentialGenerator::discard(unsigned long long n)
{
	gen.discard(n);
}

double LinearCongruentialGenerator::min()
{
    return static_cast<double>(gen.min());
}

double LinearCongruentialGenerator::max()
{
    return static_cast<double>(gen.max());
}
