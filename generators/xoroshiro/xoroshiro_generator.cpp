#include "xoroshiro_generator.h"

#include <stdint.h>
#include <iostream>

XoroshiroGenerator::XoroshiroGenerator(int seed)
    : RandomNumberGenerator(seed, "Xoroshiro"), seed64(static_cast<uint64_t>(seed))
{
    s[0] = seed64;
    s[1] = seed64 ^ 0xdeadbeefdeadbeef;
    s[2] = ~seed64;
    s[3] = seed64 ^ 0xfeedbeeffeedbeef;
}

void XoroshiroGenerator::seed(int s)
{
    seed_val = s;
    seed64 = static_cast<uint64_t>(s);
}

double XoroshiroGenerator::operator()()
{
    return transform_to_range(MIN_VAL, MAX_VAL, next());
}

void XoroshiroGenerator::discard(unsigned long long n)
{
	for (long long unsigned i = 0; i < n; ++i)
	{
		next();
	}
}

double XoroshiroGenerator::min()
{
    return MIN_VAL;
}

double XoroshiroGenerator::max()
{
    return MAX_VAL;
}

inline uint64_t XoroshiroGenerator::rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

double XoroshiroGenerator::next()
{
    const uint64_t result = s[0] + s[3];

    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;

    s[3] = rotl(s[3], 45);

    return (result >> 11) * 0x1.0p-53;
}
