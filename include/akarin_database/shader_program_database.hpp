#ifndef SHADER_PROGRAM_SYSTEM_HPP
#define SHADER_PROGRAM_SYSTEM_HPP

#include "types/texture.hpp"

#include <array>
#include <vector>
#include <unordered_map>

struct ShaderProgram
{
    std::vector<std::size_t> m_shader_ids;
    ShaderProgram(
        const std::vector<std::size_t> &p_shader_texts) noexcept
        : m_shader_ids(p_shader_texts){};
    ShaderProgram() = default;
};

namespace ShaderProgramDatabase
{

extern std::unordered_map<std::size_t, ShaderProgram> g_shaderprogram_map;

void clean_up() noexcept;

std::size_t link_shader_codes(
    const std::vector<std::size_t> &p_shaders) noexcept;

void set_shader_program_texture(
    const std::size_t,
    const std::vector<std::size_t> &) noexcept;

void clear_material(
    const std::size_t) noexcept;
}; // namespace ShaderProgramDatabase

#endif