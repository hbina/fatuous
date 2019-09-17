#pragma once

#include <array>
#include <string>
#include <iostream>

struct Texture
{
  GLuint m_id = 0;

  Texture() = delete;
  Texture(const std::size_t);
};
