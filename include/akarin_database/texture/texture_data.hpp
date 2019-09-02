#ifndef TEXTURE_DATA_HPP
#define TEXTURE_DATA_HPP

#include "glad/glad.h"

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
    GLuint m_gl_id;
    TextureType m_type;
    std::string m_path;
    std::array<int, 3> m_dimension;

    // TODO :: Make this =delete later and use operator[] instead...
    TextureData() = default;
    TextureData(const GLuint,
                const TextureType,
                const std::string &,
                const std::array<int, 3> &);
};

std::ostream &operator<<(std::ostream &p_os, const TextureType p_texture_type);

#endif