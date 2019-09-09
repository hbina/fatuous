#pragma once

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
void update_depth_function() noexcept;

// Cullface
void set_cull_face(const CullFace) noexcept;
void update_cull_face() noexcept;

void gl_clear() noexcept;

}; // namespace OpenGLSettings