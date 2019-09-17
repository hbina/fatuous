#include "akarin_database/shader/shader_database.hpp"
#include "akarin_database/texture/texture_database.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<GLuint, ShaderFile> ShaderDb::shader_map;
std::unordered_map<GLuint, ShaderProgram> ShaderDb::program_map;

GLuint add_shader_file(
    const GLuint,
    const std::string &,
    const std::string &,
    const ShaderType &) noexcept;

void test_shader_code_compilation(
    const GLuint,
    const ShaderType) noexcept;

GLuint compile_shader(
    const std::string &,
    const ShaderType) noexcept;

std::string read_shader_code_file(
    const std::string &,
    const ShaderType);

void add_shader_program(
    const GLuint,
    const std::vector<GLuint> &) noexcept;

void test_shader_program_compilation(
    const GLuint,
    const std::vector<GLuint> &) noexcept;

constexpr GLuint DEFAULT_SHADER_ID = 0;

// Exposed functions

GLuint ShaderDb::load_shader_file(
    const std::string &p_filepath,
    const ShaderType p_type) noexcept
{
    const auto &shader_data = read_shader_code_file(p_filepath, p_type);
    GLuint shader_id = compile_shader(shader_data, p_type);
    if (shader_id != DEFAULT_SHADER_ID)
    {
        return add_shader_file(
            shader_id,
            p_filepath,
            shader_data,
            p_type);
    }
    return shader_id;
};

GLuint ShaderDb::link_shader_files(
    const std::vector<GLuint> &p_shaders) noexcept
{
    GLuint prg_id = glCreateProgram();
    for (const auto shader_id : p_shaders)
    {
        glAttachShader(prg_id, shader_id);
    }
    glLinkProgram(prg_id);
    test_shader_program_compilation(prg_id, p_shaders);
    add_shader_program(prg_id, p_shaders);
    return prg_id;
};

void ShaderDb::set_shader_program_texture(
    const GLuint p_shader_program_id,
    const std::vector<Texture> &textures) noexcept
{
    // TODO :: This is not normalized data structure...please consider making it so.
    for (GLint i = 0; i < static_cast<GLint>(textures.size()); i++)
    {
        switch (textures[i].m_type)
        {
        case TextureType::DIFFUSE:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.diffuse"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_gl_id);
            break;
        };
        case TextureType::HEIGHT:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.height"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_gl_id);
            break;
        };
        case TextureType::NORMAL:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.normal"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_gl_id);
            break;
        };
        case TextureType::SPECULAR:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.specular"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_gl_id);
            break;
        };
        default:
        {
            continue;
        }
        };
    }
    // TODO :: Temporary solution...need to figure out how deal with this crap
};

// Local functions

void add_shader_program(
    const GLuint p_id,
    const std::vector<GLuint> &p_shaders) noexcept
{
    ShaderDb::program_map.emplace(
        std::make_pair(
            p_id,
            ShaderProgram(p_shaders)));
};

void test_shader_program_compilation(
    const GLuint p_shader,
    const std::vector<GLuint> &p_shaders) noexcept
{
    static constexpr auto info_log_size = 1024;
    GLint success;
    GLchar info_log[info_log_size];
    glGetProgramiv(p_shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(p_shader, info_log_size, nullptr, info_log);
        std::cerr << "p_shader:" << p_shader << " shader program compilation failed"
                  << "\n";
        for (const auto &p_iter : p_shaders)
        {
            std::cerr << "id: " << p_iter << "\n";
            // std::cerr << "filepath: " << file_map.at(p_iter).m_filepath << "\n";
            // std::cerr << "type: " << file_map.at(p_iter).m_type << "\n";
        }
        std::cout << info_log << "\n";
    }
};

GLuint compile_shader(
    const std::string &p_content,
    const ShaderType p_type) noexcept
{
    GLuint shader_id = DEFAULT_SHADER_ID;

    switch (p_type)
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

    const char *shader_code_cstr = p_content.c_str();
    glShaderSource(shader_id, 1, &shader_code_cstr, nullptr);
    glCompileShader(shader_id);
    test_shader_code_compilation(shader_id, p_type);
    return shader_id;
};

void test_shader_code_compilation(
    const GLuint p_shader,
    const ShaderType p_type) noexcept
{
    static constexpr auto info_log_size = 1024;
    GLint success;
    GLchar info_log[info_log_size];
    glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(p_shader, info_log_size, nullptr, info_log);
        std::cerr << "p_shader:" << p_shader << " shader code compilation failed p_type:" << p_type << "\n";
        std::cerr << "error:" << info_log << "\n";
    }
};

std::string read_shader_code_file(
    const std::string &p_path,
    const ShaderType p_type)
{
    std::string content;
    std::ifstream ifs;
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        ifs.open(p_path);
        std::stringstream fragment_shader_stream;
        fragment_shader_stream << ifs.rdbuf();
        ifs.close();
        content = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "shader file could not be loaded p_path:" << p_path << "\n";
    }
    return content;
};

GLuint add_shader_file(
    const GLuint p_id,
    const std::string &p_filepath,
    const std::string &p_content,
    const ShaderType &p_type) noexcept
{
    ShaderDb::shader_map.emplace(
        std::make_pair(
            p_id,
            ShaderFile(p_filepath,
                       p_content,
                       p_type)));

    return p_id;
};
