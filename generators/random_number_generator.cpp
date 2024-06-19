#include "random_number_generator.h"

#include <string>

RandomNumberGenerator::RandomNumberGenerator(int s, std::string name) : seed_val(s), name(name) {}

double RandomNumberGenerator::transform_to_range(double min, double max, double val)
{
    return val * (max - min) + min;
}

std::string RandomNumberGenerator::to_string()
{
    return name + "Generator_" + std::to_string(seed_val);
}
