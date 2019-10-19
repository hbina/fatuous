#pragma once

#include "akarin_database/glfw/akarin_glfw.hpp"

#include "entt/entt.hpp"

#include <cstddef>

struct Fatuous
{
    Fatuous();
    ~Fatuous();
    void create_entity(const std::size_t) noexcept;
    void run() noexcept;
    std::size_t get_entity_count() noexcept;

private:
    entt::registry m_registry;
    AkarinGLFW m_window;
}; // namespace Fatuous
