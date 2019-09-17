#pragma once

#include "components/mesh.hpp"

#include <string>
#include <vector>

struct Model
{
    std::vector<std::size_t> m_meshes;

    Model() = delete;
    Model(
        const std::vector<std::size_t> &);
};
