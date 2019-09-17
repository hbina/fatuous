#include "akarin_database/shader/shader_program.hpp"

ShaderProgram::ShaderProgram(
    const GLuint p_id,
    const std::vector<ShaderFile> &p_shaders) noexcept
    : m_id(p_id),
      m_shaders(p_shaders){};

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}
