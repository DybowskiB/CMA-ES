#pragma once

#include "../random_number_generator.h"

#include <random>
#include <cstdint>

class LaggedFibonacciGenerator : public RandomNumberGenerator
{
public:
    LaggedFibonacciGenerator(int seed);

    void seed(int seed) override;
    double operator()() override;
    void discard(unsigned long long n) override;
    double min() override;
    double max() override;

    unsigned int next();

private:
    std::vector<unsigned int> buffer;
    int currentIndex;

    // Parameters
    const int J = 24;  // Delay
    const int K = 55;  // Period
    const int MOD = 1 << 31;  // Modul (2^31)

    void initialize();
};
