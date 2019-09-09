#include "misc/opengl_settings.hpp"

#include "glad/glad.h"

#include <iostream>

bool enable_depth_buffer = true;

void OpenGLSettings::enable(const GLEnum p_enum, const bool p_enable) noexcept
{
    switch (p_enum)
    {
    case GLEnum::DEPTH_TEST:
    {
        enable_depth_buffer = p_enable;
        p_enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }
    default:
    {
        std::cerr << "unhandled switch case at line " << __LINE__ << __FILE__ << std::endl;
    }
    };
};

void OpenGLSettings::update() noexcept {
    // Not sure if OpenGL likes it when we just change whenever?
    // changed = false;
};

void OpenGLSettings::set_depth_function(const DepthFun p_func_type) noexcept
{

    switch (p_func_type)
    {
    case DepthFun::ALWAYS:
    {
        glDepthFunc(GL_ALWAYS);
        break;
    };
    case DepthFun::EQUAL:
    {
        glDepthFunc(GL_EQUAL);
        break;
    };
    case DepthFun::GEQUAL:
    {
        glDepthFunc(GL_GEQUAL);
        break;
    };
    case DepthFun::GREATER:
    {
        glDepthFunc(GL_GREATER);
        break;
    };
    case DepthFun::LEQUAL:
    {
        glDepthFunc(GL_LEQUAL);
        break;
    };
    case DepthFun::LESS:
    {
        glDepthFunc(GL_LESS);
        break;
    };
    case DepthFun::NEVER:
    {
        glDepthFunc(GL_NEVER);
        break;
    };
    case DepthFun::NOTEQUAL:
    {
        glDepthFunc(GL_NOTEQUAL);
        break;
    };
    default:
    {
        std::cerr << "unhandled switch case " << __LINE__ << std::endl;
    };
    }
};

// TODO :: Must be cleared depending on the settings.
GLbitfield get_clear_mask()
{
    return GL_COLOR_BUFFER_BIT | (GL_DEPTH_BUFFER_BIT & enable_depth_buffer);
};

void OpenGLSettings::gl_clear() noexcept
{
    glClear(get_clear_mask());
}