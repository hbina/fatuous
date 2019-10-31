#pragma once

#include "components/lighting.hpp"

#include "glad/glad.h"

#include <unordered_map>

namespace LightingDb
{

extern std::unordered_map<int, DirectionalLight> dir_map;
extern std::unordered_map<int, PointLight> point_map;
extern std::unordered_map<int, SpotLight> spot_map;

void prepare_light(const GLuint) noexcept;
void create_dir_light() noexcept;
void create_point_light(
    const GLsizei p_width,
    const GLsizei p_height) noexcept;
void create_spot_light() noexcept;
}; // namespace LightingDb