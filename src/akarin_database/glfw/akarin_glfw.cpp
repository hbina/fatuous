#include "akarin_database/glfw/akarin_glfw.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

std::unordered_map<char, char> keyboard_keys;
glm::vec2 mouse_offset;
glm::vec2 window_dimension;

GLFWData AkarinGLFW::create_glfw_window(
    const glm::vec2 &p_dimension) noexcept
{
    glfwSetErrorCallback([](const int p_error_code, const char *p_error_description) {
        std::cerr << "GLFW error: " << p_error_code << ": " << p_error_description << "\n";
    });

    if (!glfwInit())
    {
        std::cerr << "unable to initialize GLFW -- this is an impossible error to recover" << std::endl;
        std::exit(EXIT_FAILURE); // Can't do anything about this buddy
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    GLFWwindow *window = glfwCreateWindow(
        p_dimension.x,
        p_dimension.y,
        "Fatuous",
        nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "unable to initialize GLFW -- this is an impossible error to recover" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync, can be moved to OpenGLSettings or something...
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetFramebufferSizeCallback(window, AkarinGLFW::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, AkarinGLFW::mouse_callback);
    glfwSetKeyCallback(window, AkarinGLFW::key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD"
                  << "\n";
        glfwTerminate();
    }

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io; // just to silence warnings
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char *glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

    return GLFWData(window, p_dimension);
};

void AkarinGLFW::key_callback(
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

void AkarinGLFW::framebuffer_size_callback(
    GLFWwindow *window,
    const int p_width,
    const int p_height)
{
    window_dimension.x = p_width;
    window_dimension.y = p_height;
    glViewport(0, 0, p_width, p_height);
};

// TODO :: What do I do with GLFWindow* here??
void AkarinGLFW::mouse_callback(
    GLFWwindow *p_window,
    const double p_xpos,
    const double p_ypos)
{
    static bool first_callback = true;
    const float xpos_f = static_cast<float>(p_xpos);
    const float ypos_f = static_cast<float>(p_ypos);
    static glm::vec2 last_position;
    if (first_callback)
    {
        last_position = glm::vec2(xpos_f, ypos_f);
        first_callback = false;
    }

    mouse_offset.x = xpos_f - last_position.x;
    mouse_offset.y = last_position.y - ypos_f;

    last_position.x = xpos_f;
    last_position.y = ypos_f;
};

void AkarinGLFW::update(entt::registry &p_reg) noexcept
{
    p_reg.view<GLFWData>()
        .each([&](
                  GLFWData &p_glfw_data) {
            update_glfw_data(p_glfw_data);
        });
};

void AkarinGLFW::update_glfw_data(GLFWData &p_glfw_data) noexcept
{
    p_glfw_data.update(keyboard_keys,
                       mouse_offset,
                       window_dimension);
}
