#include "akarin_database/shader/shader_program.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(
    const std::vector<GLuint> &p_shaders) noexcept
    : m_shaders(p_shaders){};
