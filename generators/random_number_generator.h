#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <vector>

// Abstract class for random number generator
class RandomNumberGenerator {
public:
    unsigned int seed;
    RandomNumberGenerator(int seed) : seed(seed) {}
    virtual double generate() = 0;
    virtual ~RandomNumberGenerator() {}
};

#endif // RANDOM_NUMBER_GENERATOR_H