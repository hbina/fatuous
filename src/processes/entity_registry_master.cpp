#include "systems/akarin_camera_system.hpp"
#include "misc/akarin_timer.hpp"
#include "processes/swarm_process.hpp"
#include "processes/rendering_process.hpp"
#include "processes/entity_registry_master.hpp"
#include "components/transform.hpp"
#include "akarin_imgui/akarin_imgui.hpp"
#include "akarin_database/mesh/mesh_database.hpp"
#include "akarin_database/model/model_database.hpp"
#include "akarin_database/shader/shader_database.hpp"
#include "akarin_database/texture/texture_database.hpp"

#include "entt/entt.hpp"

#include <array>
#include <chrono>
#include <thread>

entt::registry p_reg;

void EntityRegistryMaster::run() noexcept
{
    static bool first = true;
    if (first)
    {
        first = false;
        create_entity(ModelDb::parse_model_file("./resources/sponza/sponza.obj"));
    }
    auto delta_time = AkarinTimer::get_delta_time();
    AkarinCameraSystem::process_keyboard(delta_time);
    RenderingProcess::render(p_reg);
};

std::size_t EntityRegistryMaster::get_entity_count() noexcept
{
    return p_reg.size();
};

void EntityRegistryMaster::create_entity(
    const std::size_t p_model_id) noexcept
{
    entt::entity new_entity = p_reg.create();
    p_reg.assign<Model>(
        new_entity,
        ModelDb::map.at(p_model_id).m_model);

    p_reg.assign<Transform>(
        new_entity,
        glm::vec3(0.0f),
        glm::vec3(1.0f));
};