#pragma once

#include "enums/shader_type.hpp"

#include "glad/glad.h"

#include <string>
#include <ostream>

struct ShaderFile
{
    const std::string m_filepath;
    const std::string m_content;
    const ShaderType m_type;

    ShaderFile() = delete;
    ShaderFile(
        const std::string &p_filepath,
        const std::string &p_content,
        const ShaderType p_type);
};
