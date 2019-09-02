#ifndef TEXTURE_DATA_HPP
#define TEXTURE_DATA_HPP

#include <array>
#include <string>
#include <iostream>

enum class TextureType
{
    CUBE_MAP,
    SPECULAR,
    DIFFUSE,
    NORMAL,
    HEIGHT,
    ERROR
};

struct TextureData
{
    unsigned int m_gl_id;
    TextureType m_type;
    std::string m_path;
    std::array<int, 2> m_size;

    TextureData() = default;
    TextureData(const unsigned int,
                const TextureType,
                const std::string &,
                const std::array<int, 2> &);
};

std::ostream &operator<<(std::ostream &p_os, const TextureType p_texture_type);

#endif