#include "components/texture.hpp"

Texture::Texture(
    const GLuint p_gl_id,
    const TextureType p_type)
    : m_gl_id(p_gl_id),
      m_type(p_type){};
