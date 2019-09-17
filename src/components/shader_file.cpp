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
      m_type(p_type){};
