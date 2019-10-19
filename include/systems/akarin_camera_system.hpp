#ifndef AKARIN_CAMERA_SYSTEM_HPP
#define AKARIN_CAMERA_SYSTEM_HPP

#include "akarin_database/glfw/akarin_glfw.hpp"

#include "glm/glm.hpp"
#include "entt/entt.hpp"

struct ProjectionView
{
    glm::mat4 projection;
    glm::mat4 view;
};

namespace AkarinCameraSystem
{
void process_keyboard(
    AkarinGLFW &p_reg,
    const float p_delta_time) noexcept;
glm::mat4 get_projection(
    const AkarinGLFW &p_glfw) noexcept;
glm::mat4 get_view() noexcept;
glm::vec3 get_position() noexcept;
glm::vec3 get_front() noexcept;
}; // namespace AkarinCameraSystem

#endif