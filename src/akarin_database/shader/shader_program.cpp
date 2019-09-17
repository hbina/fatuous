#include "akarin_database/shader/shader_program.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(
    const GLuint p_id,
    const std::vector<GLuint> &p_shaders) noexcept
    : m_id(p_id),
      m_shaders(p_shaders){};

ShaderProgram::~ShaderProgram()
{
    // FIXME :: God fking dammit
    // glDeleteProgram(m_id);
}
