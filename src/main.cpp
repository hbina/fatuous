#include "systems/input_system.hpp"
#include "akarin_imgui/akarin_imgui.hpp"
#include "processes/ecs_master_process.hpp"
#include "systems/skybox_system.hpp"
#include "akarin_database/shader_program_database.hpp"
#include "processes/rendering_process.hpp"

#include "entt/entt.hpp"
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

// Some constants
static constexpr std::uint32_t SRC_WIDTH = 1366;
static constexpr std::uint32_t SRC_HEIGHT = 768;

static float delta_time = 0.0f;
static float last_frame = 0.0f;

int main(int argc, char *argv[])
{
    for (int arg_iter = 0; arg_iter < argc; arg_iter++)
    {
        std::cout << "arg " << arg_iter << ": " << argv[arg_iter] << "\n";
    }

    glfwSetErrorCallback([](const int p_error_code, const char *p_error_description) {
        std::cerr << "GLFW error: " << p_error_code << ": " << p_error_description << "\n";
    });

    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    GLFWwindow *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Akarin 3D Engine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window"
                  << "\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetFramebufferSizeCallback(window, InputSystem::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, InputSystem::mouse_callback);
    glfwSetKeyCallback(window, InputSystem::key_callback);
    InputSystem::set_window_size(glm::vec2(SRC_WIDTH, SRC_HEIGHT));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD"
                  << "\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    AkarinImgui::init(window);
    while (!glfwWindowShouldClose(window))
    {
        RenderingProcess::set_default_clear_color(AkarinImgui::get_slider_color());
        RenderingProcess::clear_screen();
        glfwPollEvents();
        const float currentFrame = static_cast<float>(glfwGetTime());
        delta_time = currentFrame - last_frame;
        last_frame = currentFrame;
        EntitySystemMaster::run(delta_time);
        SkyboxSystem::render();
        AkarinImgui::render();
        glfwSwapBuffers(window);
        std::flush(std::cout);
    }
    ShaderProgramDatabase::clean_up();
    AkarinImgui::clean_up();
    glfwTerminate();
    return 0;
};