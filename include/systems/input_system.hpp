#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include "types/transform.hpp"

#include <glm/glm.hpp>

struct GLFWwindow;

namespace InputSystem
{
void framebuffer_size_callback(GLFWwindow *, const int, const int);
void mouse_callback(GLFWwindow *, const double, const double);
void key_callback(GLFWwindow *, const int, const int, const int, const int);
bool is_pressed(const int) noexcept;
bool is_repeated(const int) noexcept;
bool is_released(const int) noexcept;
void set_window_size(const glm::vec2 &) noexcept;
const glm::vec2 get_window_size() noexcept;
const float get_window_size_ratio() noexcept;
const glm::vec2 get_mouse_offset() noexcept;
void reset_mouse_offset() noexcept;
}; // namespace InputSystem

#endif