#ifndef MESH_DATABASE_HPP
#define MESH_DATABASE_HPP

#include "components/mesh.hpp"
#include "components/vertex.hpp"
#include "components/mesh_job.hpp"

#include "entt/entt.hpp"

#include <unordered_map>

namespace MeshDb
{
extern std::unordered_map<std::size_t, Mesh> meshes_map;

Mesh create_mesh(
    const std::vector<Vertex> &,
    const std::vector<unsigned int> &,
    const std::vector<Texture> &) noexcept;

}; // namespace MeshDb

#endif