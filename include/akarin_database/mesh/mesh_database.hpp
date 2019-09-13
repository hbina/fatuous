#ifndef MESH_DATABASE_HPP
#define MESH_DATABASE_HPP

#include "akarin_database/mesh/mesh_data.hpp"
#include "types/vertex.hpp"

#include <unordered_map>

namespace MeshDb
{
// TODO :: Must check if hash conflicts
extern std::unordered_map<std::size_t, MeshData> meshes_map;

std::size_t add_mesh_job(
    const std::vector<Vertex> &,
    const std::vector<unsigned int> &,
    const std::vector<std::size_t> &) noexcept;

void execute_jobs() noexcept;

}; // namespace MeshDb

#endif