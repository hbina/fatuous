#ifndef MESH_H
#define MESH_H

#include "types/texture.hpp"
#include "types/vertex.hpp"

#include <vector>
#include <array>

class MeshData
{
public:
    unsigned int m_vao_gl_id = 0;
    unsigned int m_vbo_gl_id = 0;
    unsigned int m_ebo_gl_id = 0;
    const std::vector<Vertex> m_vertices;
    const std::vector<unsigned int> m_indices;
    const std::vector<std::size_t> m_textures;

    MeshData() = default;
    MeshData(
        const unsigned int,
        const unsigned int,
        const unsigned int,
        const std::vector<Vertex> &,
        const std::vector<unsigned int> &,
        const std::vector<std::size_t> &) noexcept;

    void draw(const std::size_t) const;
};

#endif
