#include "components/model_data.hpp"

ModelData::ModelData(
    const std::string &m_path,
    const std::vector<Mesh> &p_meshes)
    : m_path(m_path),
      m_meshes(p_meshes){};
