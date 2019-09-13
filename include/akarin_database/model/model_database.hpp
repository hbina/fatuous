#ifndef MODEL_SYSTEM_HPP
#define MODEL_SYSTEM_HPP

#include "akarin_database/texture/texture.hpp"
#include "akarin_database/model/model_data.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

namespace ModelDb
{
extern std::unordered_map<std::size_t, ModelData> models_map;

void add_model_job(const std::string &) noexcept;
}; // namespace ModelDb

#endif