#include "processes/fatuous.hpp"
#include "systems/camera_database.hpp"
#include "processes/rendering_process.hpp"
#include "akarin_database/model/model_database.hpp"
#include "misc/akarin_timer.hpp"
#include "processes/swarm_process.hpp"
#include "components/transform.hpp"
#include "akarin_imgui/akarin_imgui.hpp"
#include "akarin_database/shader/shader_database.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "akarin_database/mesh/mesh_database.hpp"

#include "entt/entt.hpp"

#include <array>
#include <chrono>
#include <thread>

Fatuous::Fatuous()
    : m_window("Fatuous", 1024, 768){};

void Fatuous::run() noexcept
{
    while (m_window.is_alive())
    {
        auto delta_time = AkarinTimer::get_delta_time();
        CameraDb::process_keyboard(
            m_window,
            delta_time);
        RenderingProcess::render(
            m_window,
            m_registry);
    }
};

std::size_t Fatuous::get_entity_count() noexcept
{
    return m_registry.size();
};

void Fatuous::create_entity(
    const std::size_t p_model_id) noexcept
{
    entt::entity new_entity = m_registry.create();
    m_registry.assign<Model>(
        new_entity,
        ModelDb::map.at(p_model_id).m_model);

    m_registry.assign<Transform>(
        new_entity,
        glm::vec3(0.0f),
        glm::vec3(1.0f));
};
