#pragma once

#include <iostream>

#define UNHANDLED_SWITCH_CASE(line, file)                                   \
    std::cerr << "unhandled switch case " << (line) << (file) << std::endl; \
    std::exit(EXIT_FAILURE);
