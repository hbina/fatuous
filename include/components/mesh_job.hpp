#pragma once

#include "components/vertex.hpp"

#include <vector>

struct MeshJob
{
    std::size_t m_id = 0;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<std::size_t> m_textures;

    MeshJob() = delete;
    MeshJob(const std::size_t p_id,
            const std::vector<Vertex> &p_vertices,
            const std::vector<unsigned int> &p_indices,
            const std::vector<std::size_t> &p_textures);
};
