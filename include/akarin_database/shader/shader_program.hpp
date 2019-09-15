#pragma once

#include "glad/glad.h"

#include <vector>

struct ShaderProgram
{
    std::vector<GLuint> m_shader_ids;
    ShaderProgram(const std::vector<GLuint> &) noexcept;
    ShaderProgram();
};