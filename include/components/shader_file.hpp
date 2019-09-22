#pragma once

#include "enums/shader_type.hpp"

#include "glad/glad.h"

#include <string>
#include <ostream>

struct ShaderFile
{
    std::string m_filepath;
    std::string m_content;
    ShaderType m_type;

    ShaderFile() = delete;
    ShaderFile(
        const std::string &p_filepath,
        const std::string &p_content,
        const ShaderType p_type);
};
