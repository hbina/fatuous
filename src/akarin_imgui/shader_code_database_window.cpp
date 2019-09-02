#include "akarin_imgui/shader_code_database_window.hpp"
#include "akarin_database/shader_code_database.hpp"


#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

#include <algorithm>
#include <sstream>
#include <ostream>
#include <string>

void ShaderCodeDatabaseWindow::render() noexcept
{
    ImGui::Begin("ShaderCode System");
    if (ImGui::CollapsingHeader("Load ShaderCodes"))
    {
        static char shader_code_text[64] = "";
        ImGui::Text("Path to shader code");
        ImGui::InputText("path:", shader_code_text, 64);
        if (ImGui::Button("Load ShaderCode"))
        {
            ShaderCodeDatabase::load_shader_code_file(shader_code_text);
        }
    }
    if (ImGui::CollapsingHeader("ShaderCodes List"))
    {
        ImGui::Text("List of ShaderCodes loaded:");
        std::for_each(
            ShaderCodeDatabase::g_shadercode_map.cbegin(),
            ShaderCodeDatabase::g_shadercode_map.cend(),
            [](const auto &p_shader_code_iter) {
                std::ostringstream out;
                out << p_shader_code_iter.second.m_shader_path << "\n";
                ImGui::Text(
                    "%lu : %s",
                    p_shader_code_iter.first,
                    out.str().c_str());
            });
    }
    ImGui::End();
};