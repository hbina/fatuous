#include "akarin_imgui/shader_program_database_window.hpp"
#include "akarin_database/shader/shader_program_database.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <ostream>
#include <sstream>
#include <algorithm>

void ShaderProgramDatabaseWindow::render() noexcept
{
    ImGui::Begin("ShaderProgram System");
    if (ImGui::CollapsingHeader("Link ShaderCodes"))
    {
        static char shader_code_text[64] = "";
        ImGui::Text("IDs of ShaderCode, separated by space");
        ImGui::InputText("id:", shader_code_text, 64);
        if (ImGui::Button("Load ShaderProgram"))
        {
            ShaderProgramDatabase::link_shader_codes({}); // TODO :: Implement this
        }
    }
    if (ImGui::CollapsingHeader("ShaderPrograms List"))
    {
        ImGui::Text("List of ShaderPrograms loaded:");
        std::for_each(
            ShaderProgramDatabase::get_instance().map.cbegin(),
            ShaderProgramDatabase::get_instance().map.cend(),
            [](const std::pair<const GLuint, ShaderProgram> &p_shader_program_iter) {
                std::ostringstream out;
                out << p_shader_program_iter.first;
                out << " : ";
                std::for_each(
                    p_shader_program_iter.second.m_shader_ids.cbegin(),
                    p_shader_program_iter.second.m_shader_ids.end(),
                    [&out](const auto &p_shader_code_id_iter) {
                        out << p_shader_code_id_iter << ", ";
                    });
                ImGui::Text(
                    "%s",
                    out.str().c_str());
            });
    }
    ImGui::End();
};
