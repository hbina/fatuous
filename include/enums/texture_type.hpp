#pragma once

#include <ostream>

enum class TextureType
{
    CUBE_MAP,
    SPECULAR,
    DIFFUSE,
    NORMAL,
    HEIGHT
};

std::ostream &operator<<(std::ostream &, const TextureType);
