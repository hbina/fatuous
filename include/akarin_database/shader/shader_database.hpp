#pragma once

#include "components/shader_file.hpp"
#include "akarin_database/shader/shader_program.hpp"

#include "glad/glad.h"
#include "entt/entt.hpp"

#include <vector>
#include <string>
#include <unordered_map>

namespace ShaderDb
{

GLuint compile_shader(
    const std::string &p_content,
    const ShaderType p_type) noexcept;

void test_shader_code_compilation(
    const GLuint,
    const ShaderType) noexcept;

void add_shader_file(
    entt::registry &p_reg,
    const GLuint,
    const std::string &,
    const std::string &,
    const ShaderType &) noexcept;

std::string read_shader_code_file(
    const std::string &,
    const ShaderType);

void add_shader_program(
    entt::registry &,
    const GLuint,
    const std::vector<GLuint> &) noexcept;

void test_shader_program_compilation(
    const GLuint,
    const std::vector<GLuint> &) noexcept;

GLuint load_shader_file(
    entt::registry &,
    const std::string &,
    const ShaderType) noexcept;

void set_shader_program_texture(
    const GLuint,
    const std::vector<std::size_t> &) noexcept;

GLuint link_shader_codes(
    entt::registry &,
    const std::vector<GLuint> &) noexcept;
}; // namespace ShaderDb
