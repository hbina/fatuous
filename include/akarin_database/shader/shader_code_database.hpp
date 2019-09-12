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
    std::string m_filepath;
    std::string m_content;
    ShaderType m_type;

    ShaderCode();
    ShaderCode(
        const std::string &,
         const std::string &, const ShaderType);
};

namespace ShaderCodeDatabase
{

extern std::unordered_map<GLuint, ShaderCode> map;

GLuint
load_shader_file(
    const std::string &,
    const ShaderType) noexcept;
}; // namespace ShaderCodeDatabase

#endif