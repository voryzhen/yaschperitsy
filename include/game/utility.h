#pragma once

#include <random>

template <typename T> T get_random(T max)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> dist(0, max);
    return static_cast<T>(dist(mt));
}
