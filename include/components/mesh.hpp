#pragma once

#include "components/texture.hpp"
#include "components/vertex.hpp"

#include "glad/glad.h"

#include <vector>
#include <array>

struct Mesh
{
    std::size_t m_id = 0;
    GLuint m_vao_gl_id = 0;
    GLuint m_vbo_gl_id = 0;
    GLuint m_ebo_gl_id = 0;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<std::size_t> m_textures;

    Mesh() = delete;
    Mesh(
        const std::size_t,
        const GLuint,
        const GLuint,
        const GLuint,
        const std::vector<Vertex> &,
        const std::vector<unsigned int> &,
        const std::vector<std::size_t> &) noexcept;

    void draw(
        const GLuint,
        const bool) const;
};
