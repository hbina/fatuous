#include "akarin_database/glfw/akarin_glfw.hpp"
#include "processes/engine.hpp"
#include "akarin_imgui/akarin_imgui.hpp"

#include "entt/entt.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    Engine engine;
    while (AkarinGLFW::alive())
    {
        Engine::run();
        std::flush(std::cout);
    }
    return 0;
};