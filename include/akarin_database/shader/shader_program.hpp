#pragma once

#include "glad/glad.h"

#include <vector>

struct ShaderProgram
{
    GLuint m_id;
    std::vector<GLuint> m_shaders;
    ShaderProgram() = delete;
    ShaderProgram(
        const GLuint,
        const std::vector<GLuint> &) noexcept;
    ~ShaderProgram();
};