#include "akarin_database/texture/texture_data.hpp"

#include "glad/glad.h"

TextureData::TextureData(
    const GLuint p_gl_id,
    const TextureType p_texture_type,
    const std::string &p_path,
    const std::array<int, 3> &p_dimension)
    : m_gl_id(p_gl_id),
      m_type(p_texture_type),
      m_path(p_path),
      m_dimension(p_dimension){};

std::ostream &operator<<(std::ostream &p_os, const TextureType p_texture_type)
{
    switch (p_texture_type)
    {
    case TextureType::DIFFUSE:
    {
        p_os << "TextureType::DIFFUSE";
        break;
    };
    case TextureType::HEIGHT:
    {
        p_os << "TextureType::HEIGHT";
        break;
    };
    case TextureType::NORMAL:
    {
        p_os << "TextureType::NORMAL";
        break;
    };
    case TextureType::SPECULAR:
    {
        p_os << "TextureType::SPECULAR";
        break;
    };
    default:
    {
        p_os << "TextureType::ERROR";
    };
    };
    return p_os;
};
