#pragma once

#include "akarin_database/glfw/glfw_data.hpp"

#include "entt/entt.hpp"

#include <unordered_map>
#include <iostream>

namespace AkarinGLFW
{
GLFWData create_glfw_window(const glm::vec2 &) noexcept;
void update(entt::registry &p_reg) noexcept;
void update_glfw_data(GLFWData &p_glfw_data) noexcept;
void framebuffer_size_callback(GLFWwindow *, const int, const int);
void mouse_callback(GLFWwindow *, const double, const double);
void key_callback(GLFWwindow *, const int, const int, const int, const int);
}; // namespace AkarinGLFW
