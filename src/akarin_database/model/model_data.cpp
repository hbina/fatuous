#include "types/model_data.hpp"

ModelData::ModelData(
    const std::string &m_path,
    const std::vector<std::size_t> &p_meshes)
    : m_path(m_path),
      m_meshes(p_meshes){};