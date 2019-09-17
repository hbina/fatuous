#ifndef MODEL_SYSTEM_HPP
#define MODEL_SYSTEM_HPP

#include "components/model.hpp"
#include "components/texture.hpp"
#include "components/model_info.hpp"

#include "entt/entt.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

namespace ModelDb
{
extern std::unordered_map<std::size_t, ModelInfo> map;

std::size_t parse_model_file(
    const std::string &) noexcept;
}; // namespace ModelDb

#endif