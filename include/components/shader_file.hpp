#pragma once

#include "enums/shader_type.hpp"

#include "glad/glad.h"

#include <string>
#include <ostream>

struct ShaderFile
{
    const GLuint m_id;
    const std::string m_filepath;
    const std::string m_content;
    const ShaderType m_type;

    ShaderFile() = delete;
    ShaderFile(
        const GLuint,
        const std::string &,
        const std::string &,
        const ShaderType);
};
