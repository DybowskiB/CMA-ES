/*#pragma once

#include "../random_number_generator.h"

#include <random>

class LinearCongruentialGenerator : public RandomNumberGenerator
{
private:
    std::minstd_rand rng;

public:
    LinearCongruentialGenerator(int);
    double operator()() override;
    void discard(int) override;
    static constexpr unsigned min();
    static constexpr unsigned max();
};*/