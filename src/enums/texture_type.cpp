#include "enums/texture_type.hpp"
#include "misc/akarin_macros.hpp"

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
        UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
    };
    };
    return p_os;
};
