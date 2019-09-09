#include "akarin_imgui/akarin_imgui.hpp"
#include "akarin_database/singleton/glfw/akarin_glfw.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_imgui/entity_database_window.hpp"
#include "akarin_imgui/model_database_window.hpp"
#include "akarin_imgui/shader_code_database_window.hpp"
#include "akarin_imgui/shader_program_database_window.hpp"
#include "akarin_imgui/opengl_settings_window.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

struct Instance
{
    Instance()
    {
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io; // just to silence warnings
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(AkarinGLFW::get_instance().window, true);
        const char *glsl_version = "#version 450";
        ImGui_ImplOpenGL3_Init(glsl_version);
    };

    ~Instance()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    };
};

bool show_entity_database_window = false;
bool show_model_database_window = false;
bool show_lighting_database_window = false;
bool show_shadercode_database_window = false;
bool show_shaderprogram_database_window = false;
bool show_opengl_settings_window = false;

void AkarinImgui::render() noexcept
{
    static Instance instance;
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
            ImGui::MenuItem("Show OpenGLSettingsWindow", nullptr, &show_opengl_settings_window);
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
    if (show_opengl_settings_window)
        OpenGLSettingsWindow::render();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};
