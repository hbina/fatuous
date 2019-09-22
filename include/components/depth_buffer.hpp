#pragma once

#include "glad/glad.h"

struct DepthBuffer
{
    GLuint m_cube_map = 0;
    GLsizei m_height = 0;
    GLsizei m_width = 0;
    GLuint m_fbo = 0;
    GLuint m_shader = 0;
    DepthBuffer() = delete;
    DepthBuffer(
        const GLsizei p_height,
        const GLsizei p_width);
};
