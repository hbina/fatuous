#include "akarin_database/shader/shader_program.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(
    const GLuint p_id,
    const std::vector<GLuint> &p_shaders) noexcept
    : m_id(p_id),
      m_shaders(p_shaders)
{
    std::cout << "created " << *this << std::endl;
};

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

std::ostream &operator<<(std::ostream &p_left, const ShaderProgram &p_right) noexcept
{
    p_left << "ShaderProgram:{\n";
    p_left << "\tm_id: " << p_right.m_id << "\n";
    for (std::size_t i = 0; i < p_right.m_shaders.size(); i++)
    {
        p_left << "\t\t" << i << ": " << p_right.m_id;
        if (i == p_right.m_shaders.size() - 1)
            p_left << "}";
        else
            p_left << "\n";
    }
    return p_left;
};
