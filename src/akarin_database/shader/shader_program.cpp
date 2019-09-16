#include "akarin_database/shader/shader_program.hpp"

ShaderProgram::ShaderProgram(
    const std::vector<GLuint> &p_shader_texts) noexcept
    : m_shader_ids(p_shader_texts){};
