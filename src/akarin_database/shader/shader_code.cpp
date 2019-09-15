#include "akarin_database/shader/shader_code.hpp"
#include "misc/akarin_macros.hpp"

ShaderCode::ShaderCode()
    : m_type(ShaderType::ERROR){};

ShaderCode::ShaderCode(
    const std::string &p_filepath,
    const std::string &p_content,
    const ShaderType p_type)
    : m_filepath(p_filepath),
      m_content(p_content),
      m_type(p_type){};

std::ostream &operator<<(std::ostream &os, const ShaderType p_type) noexcept
{
    switch (p_type)
    {
    case ShaderType::VERTEX:
    {
        os << "ShaderType::VERTEX";
        break;
    };
    case ShaderType::FRAGMENT:
    {
        os << "ShaderType::FRAGMENT";
        break;
    };
    case ShaderType::GEOMETRY:
    {
        os << "ShaderType::GEOMETRY";
        break;
    };
    default:
    {
        UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
    }
    };
    return os;
};
