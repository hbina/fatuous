#ifndef AKARIN_CAMERA_SYSTEM_HPP
#define AKARIN_CAMERA_SYSTEM_HPP

#include "glm/glm.hpp"

struct ProjectionView
{
    glm::mat4 projection;
    glm::mat4 view;
};

namespace AkarinCameraSystem
{
void process_keyboard(const double) noexcept;
glm::mat4 get_projection() noexcept;
glm::mat4 get_view() noexcept;
glm::vec3 get_position() noexcept;
glm::vec3 get_front() noexcept;
}; // namespace AkarinCameraSystem

#endif