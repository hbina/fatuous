#include "akarin_imgui/shader_database_window.hpp"
#include "akarin_database/shader/shader_database.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <ostream>
#include <sstream>
#include <algorithm>

void ShaderDbWindow::render(entt::registry &p_reg) noexcept
{
    if (ImGui::CollapsingHeader("Shader Files"))
    {
        if (ImGui::CollapsingHeader("Load Shader Files"))
        {
            static char shader_code_text[64] = "";
            ImGui::Text("Path to shader file");
            ImGui::InputText("path:", shader_code_text, 64);
            if (ImGui::Button("Load Shader file"))
            {
                // TODO :: Dummy, fix later. Add a combo
                ShaderDb::load_shader_file(
                    p_reg,
                    shader_code_text,
                    ShaderType::VERTEX);
            }
        }
        if (ImGui::CollapsingHeader("Shader Files List"))
        {
            ImGui::Text("List of Shader files loaded:");

            p_reg.view<ShaderFile>().each([](const ShaderFile &p_iter) {
                std::ostringstream out;
                out << p_iter << "\n";
                ImGui::Text(
                    "%s",
                    out.str().c_str());
            });
        }
    }
    if (ImGui::CollapsingHeader("Shader Programs"))
    {
        // TODO :: Redesign how these works...
        if (ImGui::CollapsingHeader("Link Shader files"))
        {
            static char shader_code_text[64] = "";
            ImGui::Text("IDs of ShaderFile, separated by space");
            ImGui::InputText("id:", shader_code_text, 64);
            if (ImGui::Button("Load Shader Program"))
            {
                // ShaderDb::link_shader_codes({}); // TODO :: Implement this
            }
        }
        if (ImGui::CollapsingHeader("Shader Programs List"))
        {
            ImGui::Text("List of Shader programs loaded:");
            p_reg.view<ShaderProgram>().each([](const ShaderProgram &prg_iter) {
                std::ostringstream out;
                out << prg_iter << "\n";
                ImGui::Text(
                    "%s",
                    out.str().c_str());
            });
        }
    }
};
