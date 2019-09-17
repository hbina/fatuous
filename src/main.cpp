#include "akarin_database/glfw/akarin_glfw.hpp"
#include "processes/entity_registry_master.hpp"
#include "akarin_imgui/akarin_imgui.hpp"

#include "entt/entt.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    while (AkarinGLFW::get_instance().alive())
    {
        EntityRegistryMaster::run();
        std::flush(std::cout);
    }
    return 0;
};