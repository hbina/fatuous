#pragma once

#include "akarin_database/glfw/akarin_glfw.hpp"

enum class GLEnum
{
    DEPTH_TEST,
    CULL_FACE,
};

enum class CullFace
{
    FRONT,
    BACK,
    FRONT_AND_BACK,
};

enum class DepthFun
{
    ALWAYS,
    NEVER,
    LESS,
    EQUAL,
    LEQUAL,
    GREATER,
    NOTEQUAL,
    GEQUAL,
};

namespace OpenGLSettings
{

void enable(const GLEnum, const bool) noexcept;
void update() noexcept;

// Depth test
void set_depth_function(const DepthFun) noexcept;

// Cullface
void set_cull_face(const CullFace) noexcept;

// Exposed functions
void refresh_settings() noexcept;
void gl_clear(const GLFWData &p_glfw) noexcept;

}; // namespace OpenGLSettings
