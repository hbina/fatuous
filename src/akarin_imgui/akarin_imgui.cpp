#include "akarin_imgui/akarin_imgui.hpp"
#include "processes/ecs_master_process.hpp"
#include "akarin_database/model_database.hpp"
#include "akarin_database/shader_code_database.hpp"
#include "akarin_database/shader_program_database.hpp"
#include "types/transform.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_imgui/entity_database_window.hpp"
#include "akarin_imgui/model_database_window.hpp"
#include "akarin_imgui/shader_code_database_window.hpp"
#include "akarin_imgui/shader_program_database_window.hpp"


#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

void AkarinImgui::init(GLFWwindow *p_window) noexcept
{
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io; // just to silence warnings
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    const char *glsl_version = "#version 450";
    ImGui_ImplOpenGL3_Init(glsl_version);
};

bool show_entity_database_window = false;
bool show_model_database_window = false;
bool show_lighting_database_window = false;
bool show_shadercode_database_window = false;
bool show_shaderprogram_database_window = false;

void AkarinImgui::render() noexcept
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Windows"))
        {
            ImGui::MenuItem("Show EntityDatabaseWindow", nullptr, &show_entity_database_window);
            ImGui::MenuItem("Show ModelDatabaseWindow", nullptr, &show_model_database_window);
            ImGui::MenuItem("Show LightingDatabaseWindow", nullptr, &show_lighting_database_window);
            ImGui::MenuItem("Show ShaderCodeDatabaseWindow", nullptr, &show_shadercode_database_window);
            ImGui::MenuItem("Show ShaderProgramDatabaseWindow", nullptr, &show_shaderprogram_database_window);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if (show_entity_database_window)
        EntityDatabaseWindow::render();
    if (show_model_database_window)
        ModelDatabaseWindow::render();
    if (show_lighting_database_window)
        LightingDatabaseWindow::render();
    if (show_shadercode_database_window)
        ShaderCodeDatabaseWindow::render();
    if (show_shaderprogram_database_window)
        ShaderProgramDatabaseWindow::render();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};

std::array<float, 4> clear_color;

glm::vec4 AkarinImgui::get_slider_color() noexcept
{
    return glm::vec4(
        clear_color[0],
        clear_color[1],
        clear_color[2],
        clear_color[3]);
};

void AkarinImgui::clean_up() noexcept
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
};
