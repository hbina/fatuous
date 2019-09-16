#pragma once

#include "akarin_database/shader/shader_file.hpp"
#include "akarin_database/shader/shader_program.hpp"

#include "glad/glad.h"

#include <vector>
#include <unordered_map>

class ShaderDb
{
    // Shader files
    GLuint compile_shader(
        const ShaderFile &) noexcept;

    void test_shader_code_compilation(
        const GLuint,
        const ShaderType) noexcept;

    void add_shader_code(
        const GLuint,
        const ShaderFile &) noexcept;

    ShaderFile read_shader_code_file(
        const std::string &,
        const ShaderType);

    // Shader programs functions

    void test_shader_program_compilation(
        const GLuint) noexcept;

    ShaderDb() = default;
    ~ShaderDb();

public:
    // Shader file functions

    GLuint load_shader_file(
        const std::string &,
        const ShaderType) noexcept;

    // Shader program functions
    void set_shader_program_texture(
        const GLuint,
        const std::vector<std::size_t> &) noexcept;

    GLuint link_shader_codes(
        const std::vector<GLuint> &) noexcept;

    // Public members
    std::unordered_map<GLuint, ShaderFile> file_map;
    std::unordered_map<GLuint, ShaderProgram> program_map;

    static ShaderDb &get() noexcept;
};
