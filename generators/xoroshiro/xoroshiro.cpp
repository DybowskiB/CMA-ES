#include "xoroshiro.h"
#include <cstdint>
#include <iostream>

Xoroshiro::Xoroshiro(uint64_t seed) : RandomNumberGenerator(seed)
{
    s[0] = seed;
    s[1] = seed ^ 0xdeadbeefdeadbeef;
    s[2] = ~seed;
    s[3] = seed ^ 0xfeedbeeffeedbeef;
}

double Xoroshiro::generate(double a, double b)
{
    check_jump();
    uint64_t rand = next();
    double normalized = static_cast<double>(rand) / std::numeric_limits<uint64_t>::max();
    return transform_to_range(normalized, a, b);
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

void Xoroshiro::check_jump()
{
    counter++;
    if (counter % 3 == 0)
    {
        long_jump();
    }
    else if (counter % 2 == 0)
    {
        jump();
    }
}

/*
    This is the jump function for the generator. It is equivalent
    to 2^128 calls to next(); it can be used to generate 2^128
    non-overlapping subsequences for parallel computations.
*/
void Xoroshiro::jump(void) {
	static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	uint64_t s2 = 0;
	uint64_t s3 = 0;
	for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
		for(int b = 0; b < 64; b++) {
			if (JUMP[i] & UINT64_C(1) << b) {
				s0 ^= s[0];
				s1 ^= s[1];
				s2 ^= s[2];
				s3 ^= s[3];
			}
			next();	
		}
		
	s[0] = s0;
	s[1] = s1;
	s[2] = s2;
	s[3] = s3;
}


/* 
    This is the long-jump function for the generator. It is equivalent to
    2^192 calls to next(); it can be used to generate 2^64 starting points,
    from each of which jump() will generate 2^64 non-overlapping
    subsequences for parallel distributed computations. 
*/
void Xoroshiro::long_jump(void) 
{
	static const uint64_t LONG_JUMP[] = { 0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635 };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	uint64_t s2 = 0;
	uint64_t s3 = 0;
	for(int i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++)
		for(int b = 0; b < 64; b++) {
			if (LONG_JUMP[i] & UINT64_C(1) << b) {
				s0 ^= s[0];
				s1 ^= s[1];
				s2 ^= s[2];
				s3 ^= s[3];
			}
			next();	
		}
		
	s[0] = s0;
	s[1] = s1;
	s[2] = s2;
	s[3] = s3;
}
