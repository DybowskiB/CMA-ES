#include "random_number_generator.h"

RandomNumberGenerator::RandomNumberGenerator(uint64_t seed) : seed(seed) {}

double RandomNumberGenerator::transform_to_range(double rand, double a, double b)
{
    return a + rand * (b - a);
}