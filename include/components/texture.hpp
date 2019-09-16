#pragma once

#include <array>
#include <string>
#include <iostream>

struct Texture
{
  std::size_t m_id;

  Texture() = delete;
  Texture(const std::size_t);
};
