#pragma once

#include "glad/glad.h"

struct DepthBuffer
{
    const GLsizei m_width;
    const GLsizei m_height;
    const GLuint m_cube_map;
    const GLuint m_fbo;
    const GLuint m_shader;
    DepthBuffer() = delete;
    DepthBuffer(
        const GLsizei p_width,
        const GLsizei p_height,
        const GLuint p_cube_map,
        const GLuint p_fbo,
        const GLuint p_shader);
};
