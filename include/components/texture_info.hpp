#pragma once

#include "components/texture.hpp"
#include "enums/texture_type.hpp"

#include "glad/glad.h"

#include <array>
#include <string>
#include <iostream>

struct TextureInfo
{
    Texture m_texture;
    std::string m_path;
    std::array<int, 3> m_dimension;

    TextureInfo() = delete;
    TextureInfo(const Texture &,
                const std::string &,
                const std::array<int, 3> &);
};
