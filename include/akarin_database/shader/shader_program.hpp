#pragma once

#include "components/shader_file.hpp"

#include "glad/glad.h"

#include <vector>

struct ShaderProgram
{
    const GLuint m_id;
    const std::vector<ShaderFile> m_shaders;
    ShaderProgram() = delete;
    ShaderProgram(
        const GLuint,
        const std::vector<ShaderFile> &) noexcept;
    ~ShaderProgram();
};