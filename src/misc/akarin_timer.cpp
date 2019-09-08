#include "misc/akarin_timer.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string.h>

// TODO :: Add a hierarchial view of markers

std::unordered_map<const char *, double> chrono_timer_marks;

double get_current_time() noexcept;

void AkarinTimer::mark_begin(
    const char *p_mark) noexcept
{
    chrono_timer_marks[p_mark] = get_current_time();
};

void AkarinTimer::mark_end(
    const char *p_mark) noexcept
{
    auto find_iter = std::find_if(
        chrono_timer_marks.cbegin(),
        chrono_timer_marks.cend(),
        [p_mark](const std::pair<const char *, double> &p_timer_iter) -> bool {
            return strcmp(p_mark, p_timer_iter.first) == 0;
        });
    if (find_iter == chrono_timer_marks.cend())
    {
        std::cerr << "you are attempting to close a marker that have not been registered"
                  << "\n";
        return;
    }

    const auto &current_time = get_current_time();
    std::cout << "timer_mark name:" << p_mark << " time:" << current_time - chrono_timer_marks[p_mark] << "\n";
};

double get_current_time() noexcept
{
    static const auto start_time = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start_time;
    return elapsed_seconds.count();
};

double AkarinTimer::get_delta_time() noexcept
{
    static auto start_time = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start_time;
    start_time = end;
    return elapsed_seconds.count();
};