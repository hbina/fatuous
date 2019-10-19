#include "processes/swarm_process.hpp"
#include "systems/camera_database.hpp"
#include "components/transform.hpp"

#include <iostream>

void update_position(
    Transform &,
    const Swarm &,
    const float);

void SwarmSystem::update(
    entt::registry &p_reg,
    const float p_delta_time)
{
    auto swarm_view = p_reg.view<Swarm, Transform>();

    for (const entt::entity &e_swarm : swarm_view)
    {
        update_position(
            swarm_view.get<Transform>(e_swarm),
            swarm_view.get<Swarm>(e_swarm),
            p_delta_time);
    }
};

void update_position(
    Transform &p_transform,
    const Swarm &p_swarm,
    const float p_delta_time)
{
    const glm::vec3 distance = CameraDb::get_position() - p_transform.m_position;
    const glm::vec3 direction = glm::normalize(distance);
    const glm::vec3 new_position = p_transform.m_position + (direction * p_swarm.value * static_cast<float>(p_delta_time));
    p_transform.m_position = new_position;
};