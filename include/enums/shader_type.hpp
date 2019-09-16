#pragma once

#include <ostream>

enum class ShaderType
{
    VERTEX,
    FRAGMENT,
    GEOMETRY
};

std::ostream &operator<<(std::ostream &, const ShaderType) noexcept;