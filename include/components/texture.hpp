#pragma once

#include "glad/glad.h"
#include "enums/texture_type.hpp"

#include <array>
#include <string>
#include <iostream>

struct Texture
{
  GLuint m_gl_id;
  TextureType m_type;

  Texture() = delete;
  Texture(const GLuint,
          const TextureType);
};
