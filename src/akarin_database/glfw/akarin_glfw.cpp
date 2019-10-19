#include "akarin_database/glfw/akarin_glfw.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

AkarinGLFW::AkarinGLFW(
    const std::string &p_name,
    const float p_width,
    const float p_height)
    : m_name(p_name),
      m_dimension(p_width, p_height)
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

    m_window = glfwCreateWindow(
        m_dimension.x,
        m_dimension.y,
        m_name.c_str(),
        nullptr, nullptr);

    if (m_window == nullptr)
    {
        std::cerr << "unable to initialize GLFW -- this is an impossible error to recover" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // V-Sync, can be moved to OpenGLSettings or something...
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetFramebufferSizeCallback(m_window, GlfwDb::framebuffer_size_callback);
    glfwSetCursorPosCallback(m_window, GlfwDb::mouse_callback);
    glfwSetKeyCallback(m_window, GlfwDb::key_callback);

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
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    const char *glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
};

bool AkarinGLFW::is_alive() const noexcept
{
    if (glfwWindowShouldClose(m_window))
        return false;
    return true;
};

void AkarinGLFW::poll_events() noexcept
{
    glfwPollEvents();
}

void AkarinGLFW::swap_buffers() noexcept
{
    glfwSwapBuffers(m_window);
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

void GlfwDb::key_callback(
    GLFWwindow *p_window,
    const int p_key,
    const int scancode, // TODO :: Figure out what this is for...
    const int action,
    const int mode)
{
    if (p_key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(p_window, GLFW_TRUE);
    }
    keyboard_keys[p_key] = action;
};

void GlfwDb::framebuffer_size_callback(
    GLFWwindow *p_window,
    const int p_width,
    const int p_height)
{
    GlfwDb::glfw_map.at(p_window).update_dimension(
        static_cast<float>(p_width),
        static_cast<float>(p_height));
    glViewport(0, 0, p_width, p_height);
};

// TODO :: What do I do with GLFWindow* here??
void GlfwDb::mouse_callback(
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

void AkarinGLFW::update_dimension(
    const float p_width,
    const float p_height) noexcept
{
    m_dimension.x = p_width;
    m_dimension.y = p_height;
};

bool AkarinGLFW::is_pressed(const int p_key) noexcept
{
    return keyboard_keys[static_cast<char>(p_key)] == GLFW_PRESS;
};

bool AkarinGLFW::is_repeated(const int p_key) noexcept
{
    return keyboard_keys[static_cast<char>(p_key)] == GLFW_REPEAT;
};

bool AkarinGLFW::is_released(const int p_key) noexcept
{
    return keyboard_keys[static_cast<char>(p_key)] == GLFW_RELEASE;
};

float AkarinGLFW::get_window_size_ratio() const noexcept
{
    return m_dimension.x / m_dimension.y;
};

const glm::vec2 AkarinGLFW::get_mouse_offset() noexcept
{
    return mouse_position_offset;
};
