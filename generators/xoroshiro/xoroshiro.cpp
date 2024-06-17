#include "xoroshiro.h"

#include <stdint.h>
#include <iostream>

Xoroshiro::Xoroshiro(int seed) : RandomDoubleNumberGenerator(seed), seed64(static_cast<uint64_t>(seed))
{
    s[0] = seed64;
    s[1] = seed64 ^ 0xdeadbeefdeadbeef;
    s[2] = ~seed64;
    s[3] = seed64 ^ 0xfeedbeeffeedbeef;
}

void Xoroshiro::seed(int s)
{
    seed_val = s;
    seed64 = static_cast<uint64_t>(s);
}

double Xoroshiro::operator()()
{
    return next();
}

void Xoroshiro::discard(int n)
{
	for (int i = 0; i < n; ++i)
	{
		next();
	}
}

double Xoroshiro::min()
{
    return 0.0;
}

double Xoroshiro::max()
{
    return 1.0;
}

inline uint64_t Xoroshiro::rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

double Xoroshiro::next()
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
