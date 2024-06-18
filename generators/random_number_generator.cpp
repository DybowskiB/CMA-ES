#include "random_number_generator.h"

RandomNumberGenerator::RandomNumberGenerator(int s) : seed_val(s) {}

double RandomNumberGenerator::transform_to_range(double min, double max, double val)
{
    return val * (max - min) + min;
}
