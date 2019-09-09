#include "akarin_database/singleton/glfw/akarin_glfw.hpp"
#include "processes/entity_registry_master.hpp"
#include "akarin_imgui/akarin_imgui.hpp"

#include "entt/entt.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    for (int arg_iter = 0; arg_iter < argc; arg_iter++)
    {
        std::cout << "arg " << arg_iter << ": " << argv[arg_iter] << "\n";
    }

    while (AkarinGLFW::get_instance().alive())
    {
        EntityRegistryMaster::run();
        std::flush(std::cout);
    }
    return 0;
};