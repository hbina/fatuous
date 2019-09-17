#pragma once

#include <string>
#include <vector>

struct Model
{
    std::string m_path;
    std::vector<std::size_t> m_meshes;

    Model() = delete;
    Model(
        const std::string &,
        const std::vector<std::size_t> &);
};
