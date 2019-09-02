#include "systems/input_system.hpp"
#include "entt/entt.hpp"
#include "types/transform.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <unordered_map>
#include <iostream>

std::unordered_map<char, char> g_keyboard_keys;
glm::vec2 g_mouse_position_offset, g_last_mouse_position, g_window_size;
bool g_mouse_first_callback = false;

void InputSystem::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    g_keyboard_keys[key] = action;
};

void InputSystem::framebuffer_size_callback(GLFWwindow *window, const int p_width, const int p_height)
{
    g_window_size.x = static_cast<float>(p_width);
    g_window_size.y = static_cast<float>(p_height);
    glViewport(0, 0, p_width, p_height);
};

void InputSystem::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    g_mouse_first_callback = true;
    static bool first_mouse_callback = true;
    if (first_mouse_callback)
    {
        g_last_mouse_position = glm::vec2(xpos, ypos);
        first_mouse_callback = false;
    }

    g_mouse_position_offset.x = xpos - g_last_mouse_position.x;
    g_mouse_position_offset.y = g_last_mouse_position.y - ypos;

    g_last_mouse_position.x = xpos;
    g_last_mouse_position.y = ypos;
};

bool InputSystem::is_pressed(const int key) noexcept
{
    return g_keyboard_keys[static_cast<char>(key)] == GLFW_PRESS;
};

bool InputSystem::is_repeated(const int key) noexcept
{
    return g_keyboard_keys[static_cast<char>(key)] == GLFW_REPEAT;
};

bool InputSystem::is_released(const int key) noexcept
{
    return g_keyboard_keys[static_cast<char>(key)] == GLFW_RELEASE;
};

const glm::vec2 InputSystem::get_window_size() noexcept
{
    return g_window_size;
};

const float InputSystem::get_window_size_ratio() noexcept
{
    return g_window_size.x / g_window_size.y;
};

const glm::vec2 InputSystem::get_mouse_offset() noexcept
{
    return g_mouse_position_offset;
};

void InputSystem::reset_mouse_offset() noexcept
{
    g_mouse_position_offset = glm::vec2(0.0f);
};

void InputSystem::set_window_size(const glm::vec2 &p_window_size) noexcept
{
    g_window_size = p_window_size;
};