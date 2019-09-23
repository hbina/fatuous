#ifndef TEXTURE_SYSTEM_HPP
#define TEXTURE_SYSTEM_HPP

#include "components/texture_info.hpp"
#include "components/texture_job.hpp"
#include "components/texture.hpp"

#include <array>
#include <string>
#include <unordered_map>

namespace TextureDb
{

extern std::unordered_map<GLuint, TextureInfo> map;

GLuint load_cube_texture(
    const std::array<std::string, 6> &) noexcept;

Texture create_gl_texture(
    const std::string &,
    const TextureType) noexcept;

}; // namespace TextureDb
#endif