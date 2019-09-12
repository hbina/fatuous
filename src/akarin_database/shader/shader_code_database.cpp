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
    : m_type(ShaderType::ERROR){};

ShaderCode::ShaderCode(
    const std::string &p_filepath,
    const std::string &p_content,
    const ShaderType p_type)
    : m_filepath(p_filepath),
      m_content(p_content),
      m_type(p_type){};

constexpr GLuint DEFAULT_SHADER_ID = 0;

std::unordered_map<GLuint, ShaderCode> ShaderCodeDatabase::map;

void add_shader_code(
    const GLuint p_shader_code_id,
    const ShaderCode &p_shader_code) noexcept
{
    ShaderCodeDatabase::map[p_shader_code_id] = p_shader_code;
};

// Free function declarations
ShaderCode read_shader_code_file(
    const std::string &,
    const ShaderType);

void test_shader_code_compilation(
    GLuint, const ShaderType) noexcept;

GLuint compile_shader(
    const ShaderCode &) noexcept;

// Namespace function definitions

GLuint ShaderCodeDatabase::load_shader_file(
    const std::string &p_filepath,
    const ShaderType p_type) noexcept
{
    const auto &find_iter = std::find_if(
        ShaderCodeDatabase::map.cbegin(),
        ShaderCodeDatabase::map.cend(),
        [p_filepath](const auto &p_iter) -> bool {
            return p_iter.second.m_filepath == p_filepath;
        });
    if (find_iter != ShaderCodeDatabase::map.cend())
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

ShaderCode read_shader_code_file(
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

    switch (p_shader_code.m_type)
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
    case ShaderType::GEOMETRY:
    {
        shader_id = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    }
    default:
    {
        std::cerr << "unable to compile shader"
                  << "\n";
        return shader_id;
    };
    };

    const char *shader_code_cstr = p_shader_code.m_content.c_str();
    glShaderSource(shader_id, 1, &shader_code_cstr, nullptr);
    glCompileShader(shader_id);
    test_shader_code_compilation(shader_id, p_shader_code.m_type);
    return shader_id;
};

void test_shader_code_compilation(GLuint p_shader, const ShaderType p_type) noexcept
{
    static constexpr auto info_log_size = 1024;
    GLint success;
    GLchar info_log[info_log_size];
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
    case ShaderType::GEOMETRY:
    {
        os << "ShaderType::GEOMETRY";
        break;
    };
    default:
    {
        UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
    }
    };
    return os;
};
