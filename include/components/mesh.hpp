#pragma once

#include "components/texture.hpp"
#include "components/vertex.hpp"

#include "glad/glad.h"

#include <vector>
#include <array>

struct Mesh
{
    const GLuint m_vao_id = 0u;
    const GLuint m_vbo_id = 0u;
    const GLuint m_ebo_id = 0u;
    const std::vector<Vertex> m_vertices;
    const std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;

    Mesh() = delete;
    Mesh(
        const GLuint p_vao_id,
        const GLuint p_vbo_id,
        const GLuint p_ebo_id,
        const std::vector<Vertex> &p_vertices,
        const std::vector<unsigned int> &p_indices,
        const std::vector<Texture> &p_textures) noexcept;

    void draw(
        const GLuint p_shader_id,
        const bool p_draw_depth) const;
};
