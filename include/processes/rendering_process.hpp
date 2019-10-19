#ifndef RENDERING_SYSTEM_HPP
#define RENDERING_SYSTEM_HPP

#include "akarin_database/glfw/akarin_glfw.hpp"

#include "entt/entt.hpp"

namespace RenderingProcess
{
void render(
    AkarinGLFW &p_window,
    entt::registry &) noexcept;
}; // namespace RenderingProcess

#endif