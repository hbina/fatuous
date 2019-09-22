#pragma once

#include "enums/texture_type.hpp"

#include "glad/glad.h"

#include <array>
#include <string>
#include <iostream>

struct TextureInfo
{
    GLuint m_gl_id = 0u;
    TextureType m_type;
    std::string m_path;
    std::array<int, 3> m_dimension;

    TextureInfo() = delete;
    TextureInfo(const GLuint,
                const TextureType,
                const std::string &,
                const std::array<int, 3> &);
};
