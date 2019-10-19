#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <unordered_map>
#include <iostream>

struct AkarinGLFW
{
    AkarinGLFW(
        const std::string &p_name,
        const float p_width,
        const float p_height);
    ~AkarinGLFW();

    bool is_alive() const noexcept;
    void poll_events() noexcept;
    void update_dimension(
        const float p_width,
        const float p_height) noexcept;
    void swap_buffers() noexcept;
    bool is_pressed(const int p_key) noexcept;
    bool is_repeated(const int p_key) noexcept;
    bool is_released(const int p_key) noexcept;
    float get_window_size_ratio() const noexcept;
    const glm::vec2 get_mouse_offset() noexcept;

    std::string m_name;
    glm::vec2 m_dimension;
    GLFWwindow *m_window;
};

namespace GlfwDb
{
extern std::unordered_map<GLFWwindow *, AkarinGLFW> glfw_map;

static void framebuffer_size_callback(GLFWwindow *, const int, const int);
static void mouse_callback(GLFWwindow *, const double, const double);
static void key_callback(GLFWwindow *, const int, const int, const int, const int);
}; // namespace GlfwDb
