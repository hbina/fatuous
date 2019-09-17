#include "components/texture_info.hpp"

#include "glad/glad.h"

TextureInfo::TextureInfo(
    const Texture &p_texture,
    const std::string &p_path,
    const std::array<int, 3> &p_dimension)
    : m_texture(p_texture),
      m_path(p_path),
      m_dimension(p_dimension){};
