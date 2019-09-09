#include "akarin_database/singleton/glfw/akarin_glfw.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

glm::vec<2, int> AkarinGLFW::window_dimension = glm::vec<2, int>(1366, 768);

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
    glfwTerminate();
};

// Static functions

std::unordered_map<char, char> keyboard_keys;
glm::vec<2, double> mouse_position_offset;

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
    static glm::vec<2, double> last_mouse_position;
    if (first_mouse_callback)
    {
        last_mouse_position = glm::vec<2, double>(p_xpos, p_ypos);
        first_mouse_callback = false;
    }

    mouse_position_offset.x = p_xpos - last_mouse_position.x;
    mouse_position_offset.y = last_mouse_position.y - p_ypos;

    last_mouse_position.x = p_xpos;
    last_mouse_position.y = p_ypos;
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

const double AkarinGLFW::get_window_size_ratio() noexcept
{
    return window_dimension.x / window_dimension.y;
};

const glm::vec2 AkarinGLFW::get_mouse_offset() noexcept
{
    return mouse_position_offset;
};