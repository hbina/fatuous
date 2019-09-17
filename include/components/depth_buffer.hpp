#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

struct DepthBuffer
{
     GLuint m_shader;
     GLuint m_fbo;
     GLuint m_cube_map;
     float m_near;
     float m_far;
     glm::vec<2, GLsizei> m_dimension;

    DepthBuffer() = delete;
    DepthBuffer(const glm::vec<2, GLsizei> &);
};
