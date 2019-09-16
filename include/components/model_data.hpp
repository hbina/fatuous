#pragma once

#include <string>
#include <vector>

struct ModelData
{
    std::string m_path;
    std::vector<std::size_t> m_meshes;

    ModelData() = delete;
    ModelData(
        const std::string &,
        const std::vector<std::size_t> &);
};
