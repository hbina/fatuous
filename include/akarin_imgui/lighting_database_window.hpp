#ifndef LIGHTING_WINDOW_HPP
#define LIGHTING_WINDOW_HPP

#include "components/lighting.hpp"

#include "glm/glm.hpp"

namespace LightingDbWindow
{

// Shadow
extern bool enable_shadow;
extern float near_plane;
extern float far_plane;

extern float shadow_bias;
extern bool enable_dir_light;
extern bool enable_point_light;
extern bool enable_spot_light;

extern SpotLight spot_light;

void render() noexcept;
}; // namespace LightingDbWindow
#endif