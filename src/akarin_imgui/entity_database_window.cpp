#include "akarin_imgui/entity_database_window.hpp"
#include "akarin_database/model/model_database.hpp"
#include "processes/entity_registry_master.hpp"
#include "types/model_data.hpp"
#include "types/transform.hpp"


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <algorithm>
#include <sstream>
#include <ostream>

std::size_t selected_model_id = 0;
std::string current_selection = "Select Model";

void EntityDatabaseWindow::render() noexcept
{
    ImGui::Begin("Entity Window");
    if (ImGui::BeginCombo("Model Selection", current_selection.c_str()))
    {
        std::for_each(
            ModelDatabase::models_map.cbegin(),
            ModelDatabase::models_map.cend(),
            [](const std::pair<const std::size_t, ModelData> &p_modeldata_iter) {
                if (ImGui::Selectable(p_modeldata_iter.second.m_path.c_str()))
                {
                    selected_model_id = p_modeldata_iter.first;
                    current_selection = p_modeldata_iter.second.m_path;
                }
                if (selected_model_id == p_modeldata_iter.first)
                {
                    ImGui::SetItemDefaultFocus();
                }
            });
        ImGui::EndCombo();
    }
    if (ImGui::Button("Create entity"))
    {
        if (selected_model_id == 0)
        {
                }
        else
        {
            EntityRegistryMaster::create_entity(static_cast<std::size_t>(selected_model_id));
        }
    }
    ImGui::SameLine();

    // TODO :: Separate this into its own StatisticsWindow
    std::ostringstream out;
    out << EntityRegistryMaster::get_entity_count();
    ImGui::Text("renderable count = %s", out.str().c_str());

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
};