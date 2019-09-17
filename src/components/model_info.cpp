#include "components/model_info.hpp"

ModelInfo::ModelInfo(
    const std::string &p_path,
    const Model &p_model)
    : m_path(p_path),
      m_model(p_model) {}