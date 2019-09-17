#pragma once

#include "enums/texture_type.hpp"

#include "glad/glad.h"

#include <array>
#include <string>
#include <iostream>

struct TextureInfo
{
    const GLuint m_gl_id;
    const TextureType m_type;
    const std::string m_path;
    const std::array<int, 3> m_dimension;

    // TODO :: Make this =delete later and use operator[] instead...
    TextureInfo() = default;
    TextureInfo(const GLuint,
                const TextureType,
                const std::string &,
                const std::array<int, 3> &);
};
