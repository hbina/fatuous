#ifndef SHADER_CODE_SYSTEM_HPP
#define SHADER_CODE_SYSTEM_HPP

#include "glad/glad.h"

#include <string>
#include <vector>
#include <unordered_map>

enum class ShaderType
{
    VERTEX,
    FRAGMENT,
    ERROR
};

struct ShaderCode
{
    std::string m_shader_path;
    std::string m_shader_text;
    ShaderType m_shader_type;

    ShaderCode();
    ShaderCode(const std::string &, const std::string &, const ShaderType);
};

namespace ShaderCodeDatabase
{

extern std::unordered_map<GLuint, ShaderCode> shader_code_map;

GLuint
load_shader_code_file(
    const std::string &) noexcept;
}; // namespace ShaderCodeDatabase

#endif