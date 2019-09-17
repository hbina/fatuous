#include "components/texture.hpp"

Texture::Texture(
    const GLuint p_id,
    const TextureType p_type)
    : m_id(p_id),
      m_type(p_type){};
