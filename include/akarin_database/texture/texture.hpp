#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <array>
#include <string>
#include <iostream>

struct Texture
{
  std::size_t m_id;

  Texture() = default;
  Texture(const std::size_t);
};

#endif
