#ifndef MODEL_SYSTEM_HPP
#define MODEL_SYSTEM_HPP

#include "types/texture.hpp"
#include "types/model_data.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

namespace ModelDb
{
extern std::unordered_map<std::size_t, ModelData> models_map;

void add_model_job(const std::string &) noexcept;
std::string get_model_path(const std::size_t) noexcept;
}; // namespace ModelDb

#endif