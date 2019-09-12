#include "akarin_database/shader/shader_code_database.hpp"
#include "misc/akarin_macros.hpp"
#include "types/texture.hpp"

#include "glad/glad.h"

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

ShaderCode::ShaderCode()
    : m_shader_type(ShaderType::ERROR){};

ShaderCode::ShaderCode(
    const std::string &p_filepath,
    const std::string &p_content,
    const ShaderType p_type)
    : m_shader_path(p_filepath),
      m_shader_text(p_content),
      m_shader_type(p_type){};

constexpr GLuint DEFAULT_SHADER_ID = 0;

std::unordered_map<GLuint, ShaderCode> ShaderCodeDatabase::shader_code_map;

void add_shader_code(
    const GLuint p_shader_code_id,
    const ShaderCode &p_shader_code) noexcept
{
    ShaderCodeDatabase::shader_code_map[p_shader_code_id] = p_shader_code;
};

// Operators declarations
std::ostream &operator<<(std::ostream &, const ShaderType) noexcept;

// Free function declarations
ShaderCode read_shader_code_file(
    const std::string &,
    const ShaderType);

void test_shader_code_compilation(
    GLuint, const ShaderType) noexcept;

GLuint compile_shader(
    const ShaderCode &) noexcept;

ShaderType get_shader_extension_type(
    const std::string &) noexcept;

// Namespace function definitions

GLuint ShaderCodeDatabase::load_shader_file(
    const std::string &p_filepath,
    const ShaderType p_type) noexcept
{
    const auto &find_iter = std::find_if(
        ShaderCodeDatabase::shader_code_map.cbegin(),
        ShaderCodeDatabase::shader_code_map.cend(),
        [p_filepath](const auto &p_iter) -> bool {
            return p_iter.second.m_shader_path == p_filepath;
        });
    if (find_iter != ShaderCodeDatabase::shader_code_map.cend())
    {
        return (*find_iter).first;
    }
    const ShaderCode &shader_data = read_shader_code_file(p_filepath, p_type);
    GLuint shader_id = compile_shader(shader_data);
    if (shader_id != DEFAULT_SHADER_ID)
    {
        add_shader_code(shader_id, shader_data);
    }
    return shader_id;
};

// Free functions definitions

ShaderType
get_shader_extension_type(
    const std::string &p_extension) noexcept
{
    std::string type_string = p_extension.substr(p_extension.find_last_of('.'), p_extension.size());
    if (type_string == ".vs")
    {
        return ShaderType::VERTEX;
    }
    else if (type_string == ".fs")
    {
        return ShaderType::FRAGMENT;
    }
    std::cerr << "unsupported shader file extension -- please abort"
              << "\n";
    return ShaderType::VERTEX;
};

ShaderCode
read_shader_code_file(
    const std::string &p_shader_path,
    const ShaderType p_type)
{
    std::string shader_code;
    std::ifstream shader_file_istream;
    shader_file_istream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shader_file_istream.open(p_shader_path);
        std::stringstream fragment_shader_stream;
        fragment_shader_stream << shader_file_istream.rdbuf();
        shader_file_istream.close();
        shader_code = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "p_shader files could not be loaded p_shader_path:" << p_shader_path << "\n";
    }
    return ShaderCode(
        p_shader_path,
        shader_code,
        p_type);
};

GLuint compile_shader(
    const ShaderCode &p_shader_code) noexcept
{
    GLuint shader_id = 0;

    switch (p_shader_code.m_shader_type)
    {
    case ShaderType::VERTEX:
    {
        shader_id = glCreateShader(GL_VERTEX_SHADER);
        break;
    };
    case ShaderType::FRAGMENT:
    {
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    };
    default:
    {
        std::cerr << "unable to compile shader"
                  << "\n";
        return shader_id;
    };
    };

    const char *shader_code_cstr = p_shader_code.m_shader_text.c_str();
    glShaderSource(shader_id, 1, &shader_code_cstr, nullptr);
    glCompileShader(shader_id);
    test_shader_code_compilation(shader_id, p_shader_code.m_shader_type);
    return shader_id;
};

void test_shader_code_compilation(GLuint p_shader, const ShaderType p_type) noexcept
{
    static constexpr auto info_log_size = 1024;
    int success;
    char info_log[info_log_size];
    glGetShaderiv(p_shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(p_shader, info_log_size, nullptr, info_log);
        std::cerr << "p_shader:" << p_shader << " shader code compilation failed p_type:" << p_type << "\n";
        std::cerr << "error:" << info_log << "\n";
    }
};

// Operators

std::ostream &operator<<(std::ostream &os, const ShaderType p_type) noexcept
{
    switch (p_type)
    {
    case ShaderType::VERTEX:
    {
        os << "ShaderType::VERTEX";
        break;
    };
    case ShaderType::FRAGMENT:
    {
        os << "ShaderType::FRAGMENT";
        break;
    };
    default:
    {
        UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
    }
    };
    return os;
};
