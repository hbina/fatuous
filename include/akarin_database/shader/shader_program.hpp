#pragma once

#include "glad/glad.h"

#include <vector>
#include <ostream>

struct ShaderProgram
{
    std::vector<GLuint> m_shaders;
    ShaderProgram() = delete;
    ShaderProgram(
        const std::vector<GLuint> &) noexcept;
};
