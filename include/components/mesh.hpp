#pragma once

#include "components/texture.hpp"
#include "components/vertex.hpp"

#include "glad/glad.h"

#include <vector>
#include <array>

struct Mesh
{
    const std::size_t m_id;
    const GLuint m_vao_gl_id;
    const GLuint m_vbo_gl_id;
    const GLuint m_ebo_gl_id;
    const std::vector<Vertex> m_vertices;
    const std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;

    Mesh() = delete;
    Mesh(
        const std::size_t,
        const GLuint,
        const GLuint,
        const GLuint,
        const std::vector<Vertex> &,
        const std::vector<unsigned int> &,
        const std::vector<Texture> &) noexcept;

    void draw(
        const GLuint,
        const bool) const;
};
