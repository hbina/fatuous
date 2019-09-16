#ifndef MESH_JOB_HPP
#define MESH_JOB_HPP

#include "components/vertex.hpp"

#include <vector>

struct MeshJob
{
    const std::size_t m_id;
    const std::vector<Vertex> m_vertices;
    const std::vector<unsigned int> m_indices;
    const std::vector<std::size_t> m_textures;

    MeshJob() = default;
    MeshJob(const std::size_t,
            const std::vector<Vertex> &,
            const std::vector<unsigned int> &,
            const std::vector<std::size_t> &);
};

#endif