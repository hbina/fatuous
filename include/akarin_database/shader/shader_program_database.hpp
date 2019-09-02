#ifndef SHADER_PROGRAM_SYSTEM_HPP
#define SHADER_PROGRAM_SYSTEM_HPP

#include "types/texture.hpp"

#include "glad/glad.h"

#include <array>
#include <vector>
#include <unordered_map>

struct ShaderProgram
{
    std::vector<GLuint> m_shader_ids;
    ShaderProgram(
        const std::vector<GLuint> &p_shader_texts) noexcept
        : m_shader_ids(p_shader_texts){};
    ShaderProgram() = default;
};

namespace ShaderProgramDatabase
{

extern std::unordered_map<GLuint, ShaderProgram> shader_program_map;

void clean_up() noexcept;

GLuint link_shader_codes(
    const std::vector<GLuint> &p_shaders) noexcept;

void set_shader_program_texture(
    const GLuint,
    const std::vector<std::size_t> &) noexcept;

void clear_material(
    const std::size_t) noexcept;
}; // namespace ShaderProgramDatabase

#endif