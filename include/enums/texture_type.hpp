#pragma once

#include <ostream>

enum class TextureType
{
    CUBE_MAP,
    SPECULAR,
    DIFFUSE,
    NORMAL,
    HEIGHT,
    ERROR
};

std::ostream &operator<<(std::ostream &, const TextureType);
