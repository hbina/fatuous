#ifndef SHADER_PROGRAM_SYSTEM_HPP
#define SHADER_PROGRAM_SYSTEM_HPP

#include "akarin_database/shader/shader_program.hpp"
#include "types/texture.hpp"

#include "glad/glad.h"

#include <array>
#include <vector>
#include <unordered_map>

struct ShaderProgramDatabase
{

    std::unordered_map<GLuint, ShaderProgram> map;

    static ShaderProgramDatabase &get_instance() noexcept;

    static GLuint link_shader_codes(
        const std::vector<GLuint> &p_shaders) noexcept;

    static void set_shader_program_texture(
        const GLuint,
        const std::vector<std::size_t> &) noexcept;

    static void clear_material(
        const std::size_t) noexcept;

private:
    ShaderProgramDatabase() = default;
    ~ShaderProgramDatabase();
};

#endif