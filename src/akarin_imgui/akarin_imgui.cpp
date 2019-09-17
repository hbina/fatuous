#include "akarin_imgui/akarin_imgui.hpp"
#include "akarin_database/singleton/glfw/akarin_glfw.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_imgui/entity_database_window.hpp"
#include "akarin_imgui/model_database_window.hpp"
#include "akarin_imgui/shader_database_window.hpp"
#include "akarin_imgui/opengl_settings_window.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

bool show_entity_database_window = false;
bool show_model_database_window = false;
bool show_lighting_database_window = false;
bool show_shadercode_database_window = false;
bool show_shaderprogram_database_window = false;
bool show_opengl_settings_window = false;

void AkarinImgui::render(entt::registry& p_reg) noexcept
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Windows"))
        {
            ImGui::MenuItem("Show EntityDatabaseWindow", nullptr, &show_entity_database_window);
            ImGui::MenuItem("Show ModelDbWindow", nullptr, &show_model_database_window);
            ImGui::MenuItem("Show LightingDbWindow", nullptr, &show_lighting_database_window);
            ImGui::MenuItem("Show ShaderDbWindow", nullptr, &show_shaderprogram_database_window);
            ImGui::MenuItem("Show OpenGLSettingsWindow", nullptr, &show_opengl_settings_window);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if (show_entity_database_window)
        EntityDatabaseWindow::render();
    if (show_model_database_window)
        ModelDbWindow::render();
    if (show_lighting_database_window)
        LightingDbWindow::render();
    if (show_shaderprogram_database_window)
        ShaderDbWindow::render(p_reg);
    if (show_opengl_settings_window)
        OpenGLSettingsWindow::render();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};
