#include "akarin_database/shader/vertex_shader.hpp"

#include <sstream>

AkarinLayouts::AkarinLayouts(
    const std::size_t p_location,
    const ShaderVariableType p_type,
    const std::string &p_name)
    : m_location(p_location),
      m_type(p_type),
      m_name(p_name){};

std::ostream &operator<<(std::ostream &, const AkarinLayouts &);

AkarinUniforms::AkarinUniforms(
    const ShaderVariableType p_type,
    const std::string &p_name)
    : m_type(p_type),
      m_name(p_name){};

std::ostream &operator<<(std::ostream &, const AkarinUniforms &);

AkarinOuts::AkarinOuts(
    const ShaderVariableType p_type,
    const std::string &p_name)
    : m_type(p_type),
      m_name(p_name){};

std::ostream &operator<<(std::ostream &, const AkarinOuts &);

VertexShader::VertexShader(
    const AkarinShaderType p_type)
    : m_type(p_type){};

void VertexShader::add_layout(
    const ShaderVariableType p_type,
    const std::string &p_name) noexcept
{
    m_layouts.emplace_back(
        p_type,
        p_name);
};

void VertexShader::add_out(
    const ShaderVariableType p_type,
    const std::string &p_name) noexcept
{
    m_outs.emplace_back(
        p_type,
        p_name);
};

void VertexShader::add_uniform(
    const ShaderVariableType p_type,
    const std::string &p_name) noexcept
{
    m_uniforms.emplace_back(
        p_type,
        p_name);
};

std::string VertexShader::generate() const noexcept
{
    std::stringstream output;
    // generate the string shader here...
    output << "#version 330 core"
           << "\n";

    for (const AkarinLayouts &layout : m_layouts)
    {
        output << layout << "\n";
    }
    for (const AkarinOuts &out : m_outs)
    {
        output << out << "\n";
    }
    for (const AkarinUniforms &uniform : m_uniforms)
    {
        output << uniform << "\n";
    }

    // Add main
    return output.str();
};

std::ostream &operator<<(std::ostream &p_os, const AkarinLayouts &p_layout)
{
    p_os << "layout(location = " << p_layout.m_location << " )";
    p_os << " in " << p_layout.m_type << " " << p_layout.m_name << ";";
    return p_os;
};

std::ostream &operator<<(std::ostream &p_os, const AkarinOuts &p_layout)
{
    p_os << "out " << p_layout.m_type << " " << p_layout.m_name << ";";
    return p_os;
};

std::ostream &operator<<(std::ostream &p_os, const AkarinUniforms &p_layout)
{
    p_os << "uniform " << p_layout.m_type << " " << p_layout.m_name << ";";
    return p_os;
};
