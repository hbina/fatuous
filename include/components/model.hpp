#pragma once

#include "components/mesh.hpp"

#include <string>
#include <vector>

struct Model
{
    std::vector<Mesh> m_meshes;

    Model() = delete;
    Model(
        const std::vector<Mesh> &p_meshes);
};
