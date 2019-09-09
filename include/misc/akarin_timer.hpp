#ifndef AKARIN_PROFILER_HPP
#define AKARIN_PROFILER_HPP

#include <chrono>

// TODO :: Add other metrics and maps
// 1. Average run time of markers
// 2. All records of markers (to allow for other analysis) -- can be turned on/off

namespace AkarinTimer
{
void mark_begin(const char *) noexcept;
void mark_end(const char *) noexcept;
float get_delta_time() noexcept;
}; // namespace AkarinTimer

// Code by LPeter1997 from C++'s slack
template <typename Fn>
auto measure_function(Fn fun)
{
    auto start = std::chrono::high_resolution_clock::now();
    fun();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = end - start;
    return elapsedTime.count();
}

#endif