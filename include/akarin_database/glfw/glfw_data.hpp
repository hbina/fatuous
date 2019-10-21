#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <unordered_map>

struct GLFWData
{
    GLFWwindow *window;
    glm::vec2 dimension;
    std::unordered_map<char, char> keys;
    glm::vec2 mouse_offset;

    bool alive() noexcept;
    void swap_buffers() noexcept;
    bool is_pressed(const int) noexcept;
    bool is_repeated(const int) noexcept;
    bool is_released(const int) noexcept;
    float get_window_size_ratio() noexcept;
    const glm::vec2 get_mouse_offset() noexcept;
    void update(
        const std::unordered_map<char, char> &keyboard_keys,
        const glm::vec2 &mouse_offset,
        const glm::vec2 &window_dimension);

    GLFWData() = default;
    GLFWData(GLFWwindow *p_window,
             const glm::vec2 &p_dimension);
    ~GLFWData();
};