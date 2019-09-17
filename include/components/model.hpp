#pragma once

#include "components/mesh.hpp"

#include <string>
#include <vector>

struct Model
{
    std::string m_path;
    std::vector<Mesh> m_meshes;

    Model() = delete;
    Model(
        const std::string &,
        const std::vector<Mesh> &);
};
