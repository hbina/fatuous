#pragma once

#include "components/lighting.hpp"

#include "glad/glad.h"

#include <unordered_map>

namespace LightingDb
{

extern std::unordered_map<std::size_t, DirectionalLight> dir_map;
extern std::unordered_map<std::size_t, PointLight> point_map;
extern std::unordered_map<std::size_t, SpotLight> spot_map;

void prepare_light(const GLuint) noexcept;
void create_dir_light() noexcept;
void create_point_light() noexcept;
void create_spot_light() noexcept;
}; // namespace LightingDb