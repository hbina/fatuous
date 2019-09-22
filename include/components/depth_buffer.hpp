#pragma once

#include "glad/glad.h"

struct DepthBuffer
{
    GLuint m_cube_map = 0u;
    GLsizei m_height = 1;
    GLsizei m_width = 1;
    GLuint m_fbo = 0u;
    GLuint m_shader = 0u;
    DepthBuffer() = delete;
    DepthBuffer(
        const GLsizei p_width,
        const GLsizei p_height,
        const GLuint p_cube_map,
        const GLuint p_fbo,
        const GLuint p_shader);
};
