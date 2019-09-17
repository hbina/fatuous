#include "components/shader_file.hpp"
#include "misc/akarin_macros.hpp"

ShaderFile::ShaderFile(
    const GLuint p_id,
    const std::string &p_filepath,
    const std::string &p_content,
    const ShaderType p_type)
    : m_id(p_id),
      m_filepath(p_filepath),
      m_content(p_content),
      m_type(p_type)
{
  std::cout << "created " << *this << "\n";
};

std::ostream &operator<<(std::ostream &p_left, const ShaderFile &p_right) noexcept
{
  p_left << "ShaderFile:{\n";
  p_left << "\tm_id: " << p_right.m_id << "\n";
  p_left << "\tm_filepath: " << p_right.m_filepath << "\n";
  p_left << "\tm_type: " << p_right.m_type << "}";
  return p_left;
};
