#pragma once

#include <chrono>
#include <cstdint>
#include <ratio>
#include <thread>

using namespace std::chrono;
using Tick = time_point<steady_clock,
                        duration<long long, std::ratio<1LL, 1000000000LL>>>;

class Timer
{
    public:
        Timer() : tick_(high_resolution_clock::now()) {};
        ~Timer() = default;

        void tick() { tick_ = high_resolution_clock::now(); }

        uint32_t delta()
        {
            return duration_cast<duration<uint32_t, std::micro>>(
                       high_resolution_clock::now() - tick_)
                .count();
        }

        void sleep(uint32_t nap)
        {
            std::this_thread::sleep_for(microseconds{ nap });
        }

    private:
        Tick tick_;
};
