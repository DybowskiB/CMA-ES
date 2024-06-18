#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>

class HaltonGenerator : public RandomNumberGenerator
{
public:
    HaltonGenerator(int seed, int dimension);

    void seed(int seed) override;
    double operator()() override;
    void discard(unsigned long long n) override;
    double min() override;
    double max() override;

    std::vector<double> next();

private:
    int dimension;
    unsigned long long int index;

    double halton(unsigned long long int index, int base, const unsigned int* perms);
};
