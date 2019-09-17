#include "akarin_database/shader/shader_database.hpp"
#include "akarin_database/texture/texture_database.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

constexpr GLuint DEFAULT_SHADER_ID = 0;

std::unordered_map<GLuint, ShaderFile> ShaderDb::file_map;
std::unordered_map<GLuint, ShaderProgram> ShaderDb::program_map;

GLuint ShaderDb::compile_shader(
    const std::string &p_shader_file,
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

    const char *shader_code_cstr = p_shader_file.c_str();
    glShaderSource(shader_id, 1, &shader_code_cstr, nullptr);
    glCompileShader(shader_id);
    test_shader_code_compilation(shader_id, p_type);
    return shader_id;
};

void ShaderDb::test_shader_code_compilation(
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

std::string ShaderDb::read_shader_code_file(
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
    return shader_code;
};

void ShaderDb::add_shader_code(
    const GLuint p_shader_code_id,
    const ShaderFile &p_shader_file) noexcept
{
    file_map.emplace(
        p_shader_code_id,
        p_shader_file);
};

ShaderFile ShaderDb::load_shader_file(
    const std::string &p_filepath,
    const ShaderType p_type) noexcept
{
    const auto &find_iter = std::find_if(
        file_map.cbegin(),
        file_map.cend(),
        [p_filepath](const auto &p_iter) -> bool {
            return p_iter.second.m_filepath == p_filepath;
        });
    if (find_iter != file_map.cend())
    {
        return (*find_iter).second;
    }
    const std::string &shader_content = read_shader_code_file(p_filepath, p_type);
    GLuint shader_id = compile_shader(shader_content, p_type);
    ShaderFile shader_file = ShaderFile(
        shader_id,
        p_filepath,
        shader_content,
        p_type);
    if (shader_id != DEFAULT_SHADER_ID)
    {
        add_shader_code(shader_id, shader_file);
    }
    return shader_file;
};

GLuint ShaderDb::link_shader_codes(
    const std::vector<ShaderFile> &p_shaders) noexcept
{
    GLuint shader_program_id = glCreateProgram();
    for (const auto shader_iter : p_shaders)
    {
        glAttachShader(shader_program_id, shader_iter.m_id);
    }
    glLinkProgram(shader_program_id);
    ShaderProgram shdr_prg = ShaderProgram(
        shader_program_id,
        p_shaders);
    program_map.emplace(
        shader_program_id,
        shdr_prg);
    test_shader_program_compilation(shdr_prg);
    return shader_program_id;
};

void ShaderDb::test_shader_program_compilation(
    const ShaderProgram &p_shader) noexcept
{
    static constexpr auto info_log_size = 1024;
    GLint success;
    GLchar info_log[info_log_size];
    glGetProgramiv(p_shader.m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(p_shader.m_id, info_log_size, nullptr, info_log);
        std::cerr << "p_shader:" << p_shader.m_id << " shader program compilation failed\n";
        for (const ShaderFile &p_iter : p_shader.m_shaders)
        {
            std::cerr << "id: " << p_iter.m_id << "\n";
            std::cerr << "filepath: " << p_iter.m_filepath << "\n";
            std::cerr << "type: " << p_iter.m_type << "\n";
        }
        std::cout << info_log << "\n";
    }
};

// Public shader file functions

// Public shader program functions

void ShaderDb::set_shader_program_texture(
    const GLuint p_shader_program_id,
    const std::vector<Texture> &textures) noexcept
{
    // TODO :: This is not normalized data structure...please consider making it so.
    for (GLint i = 0; i < textures.size(); i++)
    {
        switch (textures[i].m_type)
        {
        case TextureType::DIFFUSE:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.diffuse"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_id);
            break;
        };
        case TextureType::HEIGHT:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.height"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_id);
            break;
        };
        case TextureType::NORMAL:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.normal"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_id);
            break;
        };
        case TextureType::SPECULAR:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.specular"), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].m_id);
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
