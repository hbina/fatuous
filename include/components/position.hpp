#pragma once

#include "glm/glm.hpp"

struct Position
{
    glm::vec3 m_pos;

    Position() = delete;
    Position(const glm::vec3 &);
};
