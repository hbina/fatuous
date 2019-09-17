#pragma once

#include "components/mesh.hpp"
#include "components/model.hpp"

#include <string>
#include <vector>

struct ModelInfo
{
    const std::string m_path;
    const Model m_model;

    ModelInfo() = delete;
    ModelInfo(
        const std::string &,
        const Model &);
};
