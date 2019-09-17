#ifndef MESH_DATABASE_HPP
#define MESH_DATABASE_HPP

#include "components/mesh_data.hpp"
#include "components/vertex.hpp"

#include "entt/entt.hpp"

#include <unordered_map>

namespace MeshDb
{
// extern std::unordered_map<std::size_t, Mesh> meshes_map;

std::size_t add_mesh_job(
    entt::registry &,
    const std::vector<Vertex> &,
    const std::vector<unsigned int> &,
    const std::vector<std::size_t> &) noexcept;

void execute_jobs(
    entt::registry &) noexcept;

}; // namespace MeshDb

#endif