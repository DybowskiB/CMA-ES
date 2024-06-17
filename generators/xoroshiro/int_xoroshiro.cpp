#include "int_xoroshiro.h"

#include <stdint.h>
#include <iostream>
#include <climits>

IntXoroshiro::IntXoroshiro(int seed) : RandomIntNumberGenerator(seed), seed64(static_cast<uint64_t>(seed))
{
    s[0] = seed64;
    s[1] = seed64 ^ 0xdeadbeefdeadbeef;
    s[2] = ~seed64;
    s[3] = seed64 ^ 0xfeedbeeffeedbeef;
}

void IntXoroshiro::seed(int s)
{
    seed_val = s;
    seed64 = static_cast<uint64_t>(s);
}

int IntXoroshiro::operator()()
{
    double rand = next();
    return static_cast<int>(rand * (static_cast<double>(INT_MAX) - static_cast<double>(INT_MIN) + 1) + static_cast<double>(INT_MIN));
}

void IntXoroshiro::discard(int n)
{
	for (int i = 0; i < n; ++i)
	{
		next();
	}
}

int IntXoroshiro::min()
{
    return INT_MIN;
}

int IntXoroshiro::max()
{
    return INT_MAX;
}

inline uint64_t IntXoroshiro::rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

double IntXoroshiro::next()
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
