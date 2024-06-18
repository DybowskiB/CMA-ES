#include "chacha20.h"

#include <algorithm>
#include <iomanip>
#include <array>
#include <cstdint>

ChaCha20Generator::ChaCha20Generator(int seed)
    : RandomNumberGenerator(seed), counter_(0)
{
    this->seed(seed);
}

void ChaCha20Generator::seed(int seed)
{
    // Initialize state with seed and nonce
    seed_val = seed;
    state_ = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
        static_cast<uint32_t>(seed),
        static_cast<uint32_t>(seed),
        static_cast<uint32_t>(seed),
        static_cast<uint32_t>(seed),
        counter_,
        0x00000000, 0x00000000, 0x00000000, 0x00000000 // Nonce
    };
}

double ChaCha20Generator::operator()()
{
    chacha20_block();

    // Using the first state value as the random number
    uint32_t rand_int = state_[0];
    double scaled_value = static_cast<double>(rand_int) / std::numeric_limits<uint32_t>::max();

    return transform_to_range(MIN_VAL, MAX_VAL, scaled_value);
}

void ChaCha20Generator::discard(unsigned long long n)
{
    for (unsigned long long i = 0; i < n; ++i)
    {
        operator()();
    }
}

double ChaCha20Generator::min()
{
    return MIN_VAL;
}

double ChaCha20Generator::max()
{
    return MAX_VAL;
}

void ChaCha20Generator::chacha20_block()
{
    auto temp_state = state_;

    for (int i = 0; i < 10; ++i)
    {
        // ChaCha20 quarter rounds
        quarter_round(temp_state[0], temp_state[4],  temp_state[8], temp_state[12]);
        quarter_round(temp_state[1], temp_state[5],  temp_state[9], temp_state[13]);
        quarter_round(temp_state[2], temp_state[6], temp_state[10], temp_state[14]);
        quarter_round(temp_state[3], temp_state[7], temp_state[11], temp_state[15]);
        quarter_round(temp_state[0], temp_state[5], temp_state[10], temp_state[15]);
        quarter_round(temp_state[1], temp_state[6], temp_state[11], temp_state[12]);
        quarter_round(temp_state[2], temp_state[7],  temp_state[8], temp_state[13]);
        quarter_round(temp_state[3], temp_state[4],  temp_state[9], temp_state[14]);
    }

    for (int i = 0; i < 16; ++i)
    {
        state_[i] += temp_state[i];
    }

    ++state_[12]; // Increment the counter
}

void ChaCha20Generator::quarter_round(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d)
{
    a += b; d ^= a; d = rotate_left(d, 16);
    c += d; b ^= c; b = rotate_left(b, 12);
    a += b; d ^= a; d = rotate_left(d, 8);
    c += d; b ^= c; b = rotate_left(b, 7);
}

constexpr uint32_t ChaCha20Generator::rotate_left(uint32_t value, size_t count)
{
    return (value << count) | (value >> (32 - count));
}