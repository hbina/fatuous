#pragma once

enum class GLEnum
{
    DEPTH_TEST,
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
void set_depth_function(const DepthFun) noexcept;
void update_depth_function() noexcept;
void gl_clear() noexcept;

}; // namespace OpenGLSettings