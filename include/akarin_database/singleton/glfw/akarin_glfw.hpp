#pragma once

#include "glm/glm.hpp"

#include <unordered_map>
#include <iostream>

struct GLFWwindow;

struct AkarinGLFW
{
    GLFWwindow *window;
    AkarinGLFW(const AkarinGLFW &) = delete;

    static bool alive() noexcept;
    static void swap_buffers() noexcept;
    static glm::vec<2, int> window_dimension;
    static AkarinGLFW &get_instance();
    static bool is_pressed(const int) noexcept;
    static bool is_repeated(const int) noexcept;
    static bool is_released(const int) noexcept;
    static const double get_window_size_ratio() noexcept;
    static const glm::vec2 get_mouse_offset() noexcept;

private:
    AkarinGLFW();
    ~AkarinGLFW();
    static void framebuffer_size_callback(GLFWwindow *, const int, const int);
    static void mouse_callback(GLFWwindow *, const double, const double);
    static void key_callback(GLFWwindow *, const int, const int, const int, const int);
};
