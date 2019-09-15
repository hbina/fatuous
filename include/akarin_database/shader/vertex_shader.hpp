#pragma once

#include <unordered_map>
#include <string>
#include <vector>

enum class AkarinShaderType
{
    VERTEX,
    GEOMETRY,
    FRAGMENT,
};

enum ShaderVariableType
{
    VEC2,
    VEC3,
    MAT3,
    MAT4
};

struct AkarinLayouts
{
    std::size_t m_location;
    ShaderVariableType m_type;
    std::string m_name;

    AkarinLayouts(
        const std::size_t,
        const ShaderVariableType,
        const std::string &);
};

struct AkarinOuts
{
    ShaderVariableType m_type;
    std::string m_name;

    AkarinOuts(
        const ShaderVariableType,
        const std::string &);
};

struct AkarinUniforms
{
    ShaderVariableType m_type;
    std::string m_name;

    AkarinUniforms(
        const ShaderVariableType,
        const std::string &);
};

class VertexShader
{
    AkarinShaderType m_type;
    std::vector<AkarinLayouts> m_layouts;
    std::vector<AkarinOuts> m_outs;
    std::vector<AkarinUniforms> m_uniforms;

public:
    VertexShader() = delete;
    VertexShader(const AkarinShaderType);

    void add_layout(
        const ShaderVariableType,
        const std::string &) noexcept;

    void add_out(
        const ShaderVariableType,
        const std::string &) noexcept;

    void add_uniform(
        const ShaderVariableType,
        const std::string &) noexcept;

    std::string generate() const noexcept;
};
