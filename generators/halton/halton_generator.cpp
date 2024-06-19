#include "halton_generator.h"
#include "constants.h"

#include <iostream>
#include <vector>
#include <cmath>

HaltonGenerator::HaltonGenerator(int dimension, int seed = 0)
    : RandomNumberGenerator(seed, "Halton"), dimension(dimension), index(seed)
{
    if (dimension > HALTON_MAX_DIMENSION)
    {
        std::cerr << "Warning: Dimension exceeds the number of predefined prime bases." << std::endl;
    }
}

void HaltonGenerator::seed(int seed)
{
    seed_val = seed;
    index = seed;
}

double HaltonGenerator::operator()()
{
    return next()[0] * static_cast<double>(MAX_VAL);
}

void HaltonGenerator::discard(unsigned long long n)
{
	index += n;
}

double HaltonGenerator::min()
{
    return MIN_VAL;
}

double HaltonGenerator::max()
{
    return MAX_VAL;
}

std::vector<double> HaltonGenerator::next()
{
    std::vector<double> point(dimension);
    for (int i = 0; i < dimension; ++i)
    {
        int base = PRIMES[i % HALTON_MAX_DIMENSION];
        const unsigned int *perms = EA_PERMS;
        point[i] = halton(index + 1, base, perms);
    }
    ++index;
    return point;
}

double HaltonGenerator::halton(unsigned long long int index, int base, const unsigned int *perms)
{
    double result = 0.0;
    double f = 1.0;
    double i = static_cast<double>(index);

    while (i > 0)
    {
        f = f / base;
        result = result + f * perms[static_cast<int>(fmod(i, base))];
        i = std::floor(i / base);
    }

    return result;
}
