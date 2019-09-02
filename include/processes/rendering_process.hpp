#ifndef RENDERING_SYSTEM_HPP
#define RENDERING_SYSTEM_HPP

#include "entt/entt.hpp"
#include "glm/glm.hpp"

namespace RenderingProcess
{
void render(entt::registry &) noexcept;
void set_default_clear_color(const glm::vec4 &) noexcept;
void clear_screen() noexcept;
}; // namespace RenderingProcess

#endif