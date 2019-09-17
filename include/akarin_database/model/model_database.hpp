#ifndef MODEL_SYSTEM_HPP
#define MODEL_SYSTEM_HPP

#include "components/texture.hpp"
#include "components/model.hpp"

#include "entt/entt.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

namespace ModelDb
{
extern std::unordered_map<std::size_t, Model> map;

std::size_t add_model_job(
    const std::string &) noexcept;
}; // namespace ModelDb

#endif