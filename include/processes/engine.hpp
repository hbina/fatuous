#pragma once

#include "entt/entt.hpp"

#include <cstddef>

struct Engine
{
    // void create_entity(const std::size_t) noexcept;
    void run() noexcept;
    // std::size_t get_entity_count() noexcept;
private:
    entt::registry m_reg;
}; // namespace Engine
