#include "akarin_database/shader/shader_file.hpp"
#include "misc/akarin_macros.hpp"

ShaderFile::ShaderFile(
    const std::string &p_filepath,
    const std::string &p_content,
    const ShaderType p_type)
    : m_filepath(p_filepath),
      m_content(p_content),
      m_type(p_type){};
