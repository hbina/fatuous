#include "components/texture_info.hpp"
#include "misc/akarin_macros.hpp"

#include "glad/glad.h"

TextureInfo::TextureInfo(
    const GLuint p_gl_id,
    const TextureType p_texture_type,
    const std::string &p_path,
    const std::array<int, 3> &p_dimension)
    : m_gl_id(p_gl_id),
      m_type(p_texture_type),
      m_path(p_path),
      m_dimension(p_dimension){};
