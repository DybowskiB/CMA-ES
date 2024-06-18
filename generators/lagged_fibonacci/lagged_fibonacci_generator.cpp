#include "lagged_fibonacci_generator.h"

#include <iostream>
#include <vector>
#include <cmath>

LaggedFibonacciGenerator::LaggedFibonacciGenerator(int seed = 0)
    : RandomNumberGenerator(seed)
{
    initialize();
}

void LaggedFibonacciGenerator::seed(int seed)
{
    seed_val = seed;
    initialize();
}

double LaggedFibonacciGenerator::operator()()
{
    return static_cast<double>(next());
}

void LaggedFibonacciGenerator::discard(unsigned long long n)
{
	currentIndex = (currentIndex + n) % K;
}

double LaggedFibonacciGenerator::min()
{
    return MIN_VAL;
}

double LaggedFibonacciGenerator::max()
{
    return MAX_VAL;
}

unsigned int LaggedFibonacciGenerator::next()
{
    currentIndex = (currentIndex + 1) % K;
    buffer[currentIndex] = (buffer[(currentIndex + K - J) % K] + buffer[currentIndex]) % MOD;
    return buffer[currentIndex];
}

void LaggedFibonacciGenerator::initialize()
{
    // Initiazlize sequence using seed
    srand(seed_val);
    for (int i = 0; i < K; ++i)
    {
        buffer.push_back(rand() % MOD);
    }
    currentIndex = K - 1;
}
