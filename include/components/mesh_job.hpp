#pragma once

#include "components/vertex.hpp"

#include <vector>

struct MeshJob
{
    const int m_id;
    const std::vector<Vertex> m_vertices;
    const std::vector<unsigned int> m_indices;
    const std::vector<int> m_textures;

    MeshJob() = delete;
    MeshJob(const int p_id,
            const std::vector<Vertex> &p_vertices,
            const std::vector<unsigned int> &p_indices,
            const std::vector<int> &p_textures);
};
