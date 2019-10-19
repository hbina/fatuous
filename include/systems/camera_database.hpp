#pragma once

#include "glm/glm.hpp"

struct ProjectionView
{
    glm::mat4 projection;
    glm::mat4 view;
};

namespace CameraDb
{
void process_keyboard(const float) noexcept;
glm::mat4 get_projection() noexcept;
glm::mat4 get_view() noexcept;
glm::vec3 get_position() noexcept;
glm::vec3 get_front() noexcept;
}; // namespace CameraDb
