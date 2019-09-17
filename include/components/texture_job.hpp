#pragma once

#include "components/texture_info.hpp"

struct TextureJob
{
  const std::size_t m_id;
  const std::string m_path;
  const TextureType m_type;

  TextureJob() = delete;
  TextureJob(
      const std::size_t,
      const std::string &,
      const TextureType);
};
