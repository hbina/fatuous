#include "components/mesh_job.hpp"

MeshJob::MeshJob(
    const int p_id,
    const std::vector<Vertex> &p_vertices,
    const std::vector<unsigned int> &p_indices,
    const std::vector<int> &p_textures)
    : m_id(p_id),
      m_vertices(p_vertices),
      m_indices(p_indices),
      m_textures(p_textures){};