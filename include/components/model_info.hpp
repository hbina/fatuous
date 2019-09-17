#pragma once

#include "components/mesh.hpp"

#include <string>
#include <vector>

struct ModelInfo
{
    std::string m_path;
    std::vector<Mesh> m_meshes;

    ModelInfo() = delete;
    ModelInfo(
        const std::string &,
        const std::vector<Mesh> &);
};
