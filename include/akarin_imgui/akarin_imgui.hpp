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
glm::vec4 get_slider_color() noexcept;
}; // namespace AkarinImgui

#endif