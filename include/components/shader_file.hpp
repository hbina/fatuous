#pragma once

#include "enums/shader_type.hpp"

#include "glad/glad.h"

#include <string>
#include <ostream>

struct ShaderFile
{
    GLuint m_id;
    std::string m_filepath;
    std::string m_content;
    ShaderType m_type;

    ShaderFile() = delete;
    ShaderFile(
        const GLuint,
        const std::string &,
        const std::string &,
        const ShaderType);
};

std::ostream &operator<<(std::ostream &, const ShaderFile &) noexcept;
