#pragma once

#include "components/shader_file.hpp"
#include "components/texture.hpp"
#include "akarin_database/shader/shader_program.hpp"

#include "glad/glad.h"
#include "entt/entt.hpp"

#include <vector>
#include <string>
#include <unordered_map>

namespace ShaderDb
{
extern std::unordered_map<GLuint, ShaderFile> shader_map;
extern std::unordered_map<GLuint, ShaderProgram> program_map;

GLuint load_shader_file(
    const std::string &,
    const ShaderType) noexcept;

void set_shader_program_texture(
    const GLuint,
    const std::vector<Texture> &) noexcept;

GLuint link_shader_files(
    const std::vector<GLuint> &) noexcept;
}; // namespace ShaderDb
