#pragma once

#include "../random_number_generator.h"
#include <array>

class ChaCha20Generator : public RandomNumberGenerator
{
public:
    ChaCha20Generator(int seed);

    void seed(int seed) override;
    double operator()() override;
    void discard(unsigned long long n) override;
    double min() override;
    double max() override;

private:
    std::array<uint32_t, 16> state_;
    uint32_t counter_;

    void chacha20_block();
    void quarter_round(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);
    constexpr uint32_t rotate_left(uint32_t value, size_t count);
};
