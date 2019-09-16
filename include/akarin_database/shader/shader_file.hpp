#pragma once

#include "akarin_database/shader/shader_type.hpp"

#include <string>
#include <ostream>

struct ShaderFile
{
    std::string m_filepath;
    std::string m_content;
    ShaderType m_type;

    ShaderFile() = delete;
    ShaderFile(
        const std::string &,
        const std::string &, const ShaderType);
};