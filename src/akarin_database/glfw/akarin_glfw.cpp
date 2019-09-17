#include "akarin_database/glfw/akarin_glfw.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

glm::vec2 AkarinGLFW::window_dimension(1024, 1024);

AkarinGLFW::AkarinGLFW()
{
    glfwSetErrorCallback([](const int p_error_code, const char *p_error_description) {
        std::cerr << "GLFW error: " << p_error_code << ": " << p_error_description << "\n";
    });

    if (!glfwInit())
    {
        std::cerr << "unable to initialize GLFW -- this is an impossible error to recover" << std::endl;
        std::exit(EXIT_FAILURE); // Can't do anything about this buddy
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    window = glfwCreateWindow(
        window_dimension.x,
        window_dimension.y,
        "Akarin 3D Engine",
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
    const char *glsl_version = "#version 450";
    ImGui_ImplOpenGL3_Init(glsl_version);
};

AkarinGLFW &AkarinGLFW::get_instance()
{
    static AkarinGLFW instance;
    return instance;
};

bool AkarinGLFW::alive() noexcept
{
    if (glfwWindowShouldClose(get_instance().window))
        return false;

    glfwPollEvents();
    return true;
};

void AkarinGLFW::swap_buffers() noexcept
{
    glfwSwapBuffers(get_instance().window);
};

AkarinGLFW::~AkarinGLFW()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
};

// Static functions

std::unordered_map<char, char> keyboard_keys;
glm::vec2 mouse_position_offset;

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
    static bool first_mouse_callback = true;
    const float xpos_f = static_cast<float>(p_xpos);
    const float ypos_f = static_cast<float>(p_ypos);
    static glm::vec2 last_mouse_position;
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

bool AkarinGLFW::is_pressed(const int key) noexcept
{
    return keyboard_keys[static_cast<char>(key)] == GLFW_PRESS;
};

bool AkarinGLFW::is_repeated(const int key) noexcept
{
    return keyboard_keys[static_cast<char>(key)] == GLFW_REPEAT;
};

bool AkarinGLFW::is_released(const int key) noexcept
{
    return keyboard_keys[static_cast<char>(key)] == GLFW_RELEASE;
};

float AkarinGLFW::get_window_size_ratio() noexcept
{
    return window_dimension.x / window_dimension.y;
};

const glm::vec2 AkarinGLFW::get_mouse_offset() noexcept
{
    return mouse_position_offset;
};
