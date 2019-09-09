#ifndef ENTITY_WINDOW_HPP
#define ENTITY_WINDOW_HPP

#include "entt/entt.hpp"
#include "glm/glm.hpp"

struct GLFWwindow;

namespace AkarinImgui
{
void init(GLFWwindow *) noexcept;
void render() noexcept;
void clean_up() noexcept;
}; // namespace AkarinImgui

#endif