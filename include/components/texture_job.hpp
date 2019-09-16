#ifndef INTERMEDIATE_MODEL_SYSTEM_TYPES_HPP
#define INTERMEDIATE_MODEL_SYSTEM_TYPES_HPP

#include "components/texture_data.hpp"

struct TextureJob
{
  const std::size_t m_id;
  const std::string m_path;
  const TextureType m_type;

  TextureJob() = delete;
  TextureJob(
      const std::size_t p_id,
      const std::string &p_path,
      const TextureType p_type)
      : m_id(p_id),
        m_path(p_path),
        m_type(p_type){};
};

#endif
