#pragma once

#include "glad/glad.h"
#include "enums/texture_type.hpp"

#include <array>
#include <string>
#include <iostream>

struct Texture
{
  const GLuint m_gl_id;
  const TextureType m_type;

  Texture() = delete;
  Texture(const GLuint,
          const TextureType);
};
