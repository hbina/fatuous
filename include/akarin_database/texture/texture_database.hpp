#ifndef TEXTURE_SYSTEM_HPP
#define TEXTURE_SYSTEM_HPP

#include "components/texture_data.hpp"
#include "components/texture_job.hpp"
#include "components/texture.hpp"

#include <array>
#include <string>
#include <unordered_map>

namespace TextureDb
{

extern std::unordered_map<std::size_t, TextureData> textures_map;

Texture load_cube_texture(
    const std::array<std::string, 6> &) noexcept;

std::size_t add_texture_job(
    const std::string &,
    const TextureType) noexcept;

void execute_jobs() noexcept;

}; // namespace TextureDb
#endif