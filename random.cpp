#include "random.h"

#include <random>

uint32_t GenRandamNumber(const uint32_t min, const uint32_t max)
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<uint32_t> dis(min, max);
    return dis(eng);
}