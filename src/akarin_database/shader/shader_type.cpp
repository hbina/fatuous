#include "akarin_database/shader/shader_type.hpp"
#include "misc/akarin_macros.hpp"

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