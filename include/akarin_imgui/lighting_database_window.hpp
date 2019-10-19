#pragma once

#include "components/lighting.hpp"

#include "glm/glm.hpp"

namespace LightingDbWindow
{

// Shadow
extern bool enable_shadow;
extern bool enable_shadow_debug;
extern float near_plane;
extern float far_plane;

extern float shadow_bias;
extern bool enable_dir_light;
extern bool enable_point_light;
extern bool enable_spot_light;

void render() noexcept;
}; // namespace LightingDbWindow
