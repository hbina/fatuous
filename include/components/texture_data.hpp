#pragma once

#include "enums/texture_type.hpp"

#include "glad/glad.h"

#include <array>
#include <string>
#include <iostream>

struct TextureData
{
    GLuint m_gl_id;
    TextureType m_type;
    std::string m_path;
    std::array<int, 3> m_dimension;

    // TODO :: Make this =delete later and use operator[] instead...
    TextureData() = default;
    TextureData(const GLuint,
                const TextureType,
                const std::string &,
                const std::array<int, 3> &);
};
