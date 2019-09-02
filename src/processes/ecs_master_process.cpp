#include "processes/ecs_master_process.hpp"
#include "systems/input_system.hpp"
#include "systems/akarin_camera_system.hpp"
#include "processes/rendering_process.hpp"
#include "akarin_database/model_database.hpp"
#include "types/swarm.hpp"
#include "systems/input_system.hpp"
#include "processes/swarm_process.hpp"
#include "types/transform.hpp"
#include "akarin_imgui/akarin_imgui.hpp"
#include "akarin_database/shader_program_database.hpp"
#include "akarin_database/shader_code_database.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "akarin_database/mesh/mesh_database.hpp"
#include "types/shader.hpp"

#include "entt/entt.hpp"

#include <array>
#include <chrono>
#include <thread>

entt::registry p_reg;

float get_random_float(
    const float) noexcept;

void EntitySystemMaster::run(
    const float p_time_elapsed) noexcept
{
    AkarinCameraSystem::process_keyboard(p_time_elapsed);
    MeshDatabase::execute_jobs();
    TextureDatabase::execute_jobs();
    SwarmSystem::update(p_reg, p_time_elapsed);
    RenderingProcess::render(p_reg);
};

std::size_t EntitySystemMaster::get_entity_count() noexcept
{
    return p_reg.size();
};

void EntitySystemMaster::create_entity(
    const std::size_t p_model_id) noexcept
{
    entt::entity new_entity = p_reg.create();
    p_reg.assign<ModelData>(
        new_entity,
        ModelDatabase::models_map[p_model_id]);

    p_reg.assign<Transform>(
        new_entity,
        glm::vec3(
            get_random_float(100.0f) - 50.0f,
            get_random_float(100.0f) - 50.0f,
            get_random_float(100.0f) - 50.0f),
        glm::vec3(1.0f));
    p_reg.assign<Swarm>(
        new_entity,
        get_random_float(0.0f));
};

float get_random_float(
    const float p_value) noexcept
{
    return p_value * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
};
