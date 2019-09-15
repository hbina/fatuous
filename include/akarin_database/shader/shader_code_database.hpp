#pragma once

#include "akarin_database/shader/shader_code.hpp"

#include "glad/glad.h"

#include <string>
#include <vector>
#include <unordered_map>

// Operators declarations

namespace ShaderCodeDb
{

extern std::unordered_map<GLuint, ShaderCode> map;

GLuint load_shader_file(
    const std::string &,
    const ShaderType) noexcept;
}; // namespace ShaderCodeDb
