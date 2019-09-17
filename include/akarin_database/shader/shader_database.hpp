#pragma once

#include "components/texture.hpp"
#include "components/shader_file.hpp"
#include "akarin_database/shader/shader_program.hpp"

#include "glad/glad.h"

#include <vector>
#include <unordered_map>

namespace ShaderDb
{
// Shader files
GLuint compile_shader(
    const std::string &,
    const ShaderType) noexcept;

void test_shader_code_compilation(
    const GLuint,
    const ShaderType) noexcept;

void add_shader_code(
    const GLuint,
    const ShaderFile &) noexcept;

std::string read_shader_code_file(
    const std::string &,
    const ShaderType);

// Shader programs functions

void test_shader_program_compilation(
    const ShaderProgram &) noexcept;

// Shader file functions

ShaderFile load_shader_file(
    const std::string &,
    const ShaderType) noexcept;

// Shader program functions
void set_shader_program_texture(
    const GLuint,
    const std::vector<Texture> &) noexcept;

GLuint link_shader_codes(
    const std::vector<ShaderFile> &) noexcept;

// Public members
extern std::unordered_map<GLuint, ShaderFile> file_map;
extern std::unordered_map<GLuint, ShaderProgram> program_map;
}; // namespace ShaderDb
