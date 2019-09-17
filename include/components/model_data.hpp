#pragma once

#include "components/mesh.hpp"

#include <string>
#include <vector>

struct ModelData
{
    std::string m_path;
    std::vector<Mesh> m_meshes;

    ModelData() = delete;
    ModelData(
        const std::string &,
        const std::vector<Mesh> &);
};
