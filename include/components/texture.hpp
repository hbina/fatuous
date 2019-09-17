#pragma once

#include "enums/texture_type.hpp"
#include "glad/glad.h"

#include <array>
#include <string>
#include <iostream>

struct Texture
{
  GLuint m_id;
  TextureType m_type;

  Texture() = delete;
  Texture(
      const GLuint,
      const TextureType);
};
