#include "systems/input_system.hpp"
#include "entt/entt.hpp"
#include "types/transform.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <unordered_map>
#include <iostream>

std::unordered_map<char, char> keyboard_keys;
glm::vec2 mouse_position_offset, last_mouse_position, window_size;

void InputSystem::key_callback(
    GLFWwindow *window,
    const int key,
    const int scancode,
    const int action,
    const int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    keyboard_keys[key] = action;
};

void InputSystem::framebuffer_size_callback(
    GLFWwindow *window,
    const int p_width,
    const int p_height)
{
    window_size.x = static_cast<float>(p_width);
    window_size.y = static_cast<float>(p_height);
    glViewport(0, 0, p_width, p_height);
};

// TODO :: What do I do with GLFWindow* here??
void InputSystem::mouse_callback(
    GLFWwindow *p_window,
    const double p_xpos,
    const double p_ypos)
{
    const float xpos_f = static_cast<float>(p_xpos);
    const float ypos_f = static_cast<float>(p_ypos);
    static bool first_mouse_callback = true;
    if (first_mouse_callback)
    {
        last_mouse_position = glm::vec2(xpos_f, ypos_f);
        first_mouse_callback = false;
    }

    mouse_position_offset.x = xpos_f - last_mouse_position.x;
    mouse_position_offset.y = last_mouse_position.y - ypos_f;

    last_mouse_position.x = xpos_f;
    last_mouse_position.y = ypos_f;
};

bool InputSystem::is_pressed(const int key) noexcept
{
    return keyboard_keys[static_cast<char>(key)] == GLFW_PRESS;
};

bool InputSystem::is_repeated(const int key) noexcept
{
    return keyboard_keys[static_cast<char>(key)] == GLFW_REPEAT;
};

bool InputSystem::is_released(const int key) noexcept
{
    return keyboard_keys[static_cast<char>(key)] == GLFW_RELEASE;
};

const glm::vec2 InputSystem::get_window_size() noexcept
{
    return window_size;
};

const float InputSystem::get_window_size_ratio() noexcept
{
    return window_size.x / window_size.y;
};

const glm::vec2 InputSystem::get_mouse_offset() noexcept
{
    return mouse_position_offset;
};

void InputSystem::reset_mouse_offset() noexcept
{
    mouse_position_offset = glm::vec2(0.0f);
};

void InputSystem::set_window_size(const glm::vec2 &p_window_size) noexcept
{
    window_size = p_window_size;
};