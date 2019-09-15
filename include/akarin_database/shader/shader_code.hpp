#pragma once

#include <string>
#include <ostream>

enum class ShaderType
{
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    ERROR
};

std::ostream &operator<<(std::ostream &, const ShaderType) noexcept;

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