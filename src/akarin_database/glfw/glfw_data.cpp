#include "akarin_database/glfw/glfw_data.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

bool GLFWData::alive() noexcept
{
    if (glfwWindowShouldClose(window))
        return false;

    glfwPollEvents();
    return true;
};

void GLFWData::swap_buffers() noexcept
{
    glfwSwapBuffers(window);
};

GLFWData::~GLFWData()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
};

bool GLFWData::is_pressed(const int p_key) noexcept
{
    return keys[static_cast<char>(p_key)] == GLFW_PRESS;
};

bool GLFWData::is_repeated(const int p_key) noexcept
{
    return keys[static_cast<char>(p_key)] == GLFW_REPEAT;
};

bool GLFWData::is_released(const int p_key) noexcept
{
    return keys[static_cast<char>(p_key)] == GLFW_RELEASE;
};

float GLFWData::get_window_size_ratio() noexcept
{
    return dimension.x / dimension.y;
};

const glm::vec2 GLFWData::get_mouse_offset() noexcept
{
    return mouse_offset;
};

void GLFWData::update(
    const std::unordered_map<char, char> &p_keys,
    const glm::vec2 &p_mouse_offset,
    const glm::vec2 &p_dimension)
{
    keys = p_keys;
    mouse_offset = p_mouse_offset;
    dimension = p_dimension;
};
