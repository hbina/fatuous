#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <unordered_map>
#include <iostream>

struct AkarinGLFW
{
    AkarinGLFW(const AkarinGLFW &) = delete;

    static bool alive() noexcept;
    static void swap_buffers() noexcept;
    static glm::vec2 window_dimension;
    static AkarinGLFW &get_instance();
    static bool is_pressed(const int) noexcept;
    static bool is_repeated(const int) noexcept;
    static bool is_released(const int) noexcept;
    static float get_window_size_ratio() noexcept;
    static const glm::vec2 get_mouse_offset() noexcept;

private:
    GLFWwindow *window;
    AkarinGLFW();
    ~AkarinGLFW();
    static void framebuffer_size_callback(GLFWwindow *, const int, const int);
    static void mouse_callback(GLFWwindow *, const double, const double);
    static void key_callback(GLFWwindow *, const int, const int, const int, const int);
};
