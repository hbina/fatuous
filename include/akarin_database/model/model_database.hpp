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
#include <atomic>

namespace ModelDb
{
// extern std::unordered_map<std::size_t, ModelInfo> map;

std::size_t add_model_job(
    const std::string &) noexcept;

// Thread-safe access to table;
template <typename F, typename... Ts>
void for_each(F f, Ts...) noexcept;

const ModelInfo &get(const std::size_t) noexcept;
}; // namespace ModelDb

#endif