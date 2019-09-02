#include "akarin_database/shader/shader_program_database.hpp"
#include "akarin_database/shader/shader_code_database.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "types/shader.hpp"

#include <ostream>
#include <sstream>

std::unordered_map<GLuint, ShaderProgram> ShaderProgramDatabase::shader_program_map;

void add_shader_program(
    const GLuint p_shader_program_id,
    const ShaderProgram &p_shader_program) noexcept
{
    ShaderProgramDatabase::shader_program_map[p_shader_program_id] = p_shader_program;
};

// Free function declarations

void test_shader_program_compilation(
    const GLuint p_shader) noexcept;

// Namespace functions definitions

void ShaderProgramDatabase::clean_up() noexcept
{
    for (const auto &shader_program_id : shader_program_map)
    {
        glDeleteProgram(shader_program_id.first);
    }
    shader_program_map.clear();
};

GLuint ShaderProgramDatabase::link_shader_codes(
    const std::vector<GLuint> &p_shaders) noexcept
{
    GLuint shader_program_id = glCreateProgram();
    for (const auto shader_id : p_shaders)
    {
        glAttachShader(shader_program_id, shader_id);
        glLinkProgram(shader_program_id);
        test_shader_program_compilation(shader_program_id);
        glDeleteShader(shader_id);
    }
    add_shader_program(shader_program_id, ShaderProgram(p_shaders));
    return shader_program_id;
};

void ShaderProgramDatabase::set_shader_program_texture(
    const GLuint p_shader_program_id,
    const std::vector<std::size_t> &textures) noexcept
{
    // TODO :: This is not normalized data structure...please consider making it so.
    for (std::uint32_t i = 0; i < textures.size(); i++)
    {
        switch (TextureDatabase::textures_map[textures[i]].m_type)
        {
        case TextureType::DIFFUSE:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.diffuse"), i);
            break;
        };
        case TextureType::HEIGHT:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.height"), i);
            break;
        };
        case TextureType::NORMAL:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.normal"), i);
            break;
        };
        case TextureType::SPECULAR:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.specular"), i);
            break;
        };
        default:
        {
            continue;
        }
        };

        glBindTexture(GL_TEXTURE_2D, TextureDatabase::textures_map[textures[i]].m_gl_id);
    }
    // TODO :: Temporary solution...need to figure out how deal with this crap
};

// Free functions definitions

void test_shader_program_compilation(const GLuint p_shader) noexcept
{
    static constexpr auto info_log_size = 1024;
    int success;
    char info_log[info_log_size];
    glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(p_shader, info_log_size, nullptr, info_log);
        std::cerr << "p_shader:" << p_shader << " shader program compilation failed"
                  << "\n";
        std::cout << "error:" << info_log << "\n";
    }
};
