#include "components/texture_job.hpp"

TextureJob::TextureJob(
    const int p_id,
    const std::string &p_path,
    const TextureType p_type)
    : m_id(p_id),
      m_path(p_path),
      m_type(p_type){};