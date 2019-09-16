#include "akarin_imgui/shader_program_database_window.hpp"
#include "akarin_database/shader/shader_database.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <ostream>
#include <sstream>
#include <algorithm>

void ShaderProgramDbWindow::render() noexcept
{
    ImGui::Begin("ShaderProgram System");
    if (ImGui::CollapsingHeader("Link ShaderCodes"))
    {
        static char shader_code_text[64] = "";
        ImGui::Text("IDs of ShaderFile, separated by space");
        ImGui::InputText("id:", shader_code_text, 64);
        if (ImGui::Button("Load ShaderProgram"))
        {
            ShaderDb::get().link_shader_codes({}); // TODO :: Implement this
        }
    }
    if (ImGui::CollapsingHeader("ShaderPrograms List"))
    {
        ImGui::Text("List of ShaderPrograms loaded:");
        for (const auto &prg_iter : ShaderDb::get().program_map)
        {
            std::ostringstream out;
            out << prg_iter.first;
            out << " : ";
            for (const auto &shr_iter : prg_iter.second.m_shader_ids)
            {
                out << shr_iter << ", ";
            };
            ImGui::Text(
                "%s",
                out.str().c_str());
        };
    }
    ImGui::End();
};
