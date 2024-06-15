#include <cstdint>
#include "xoroshiro.h"

Xoroshiro::Xoroshiro(uint64_t seed) : RandomNumberGenerator(seed)
{
    s[0] = seed;
    s[1] = seed ^ 0xdeadbeefdeadbeef;
    s[2] = ~seed;
    s[3] = seed ^ 0xfeedbeeffeedbeef;
}

double Xoroshiro::generate()
{
    return (next() >> 11) * 0x1.0p-53;
}

inline uint64_t Xoroshiro::rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

uint64_t Xoroshiro::next()
{
    const uint64_t result = s[0] + s[3];

    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;

    s[3] = rotl(s[3], 45);

    return result;
}
