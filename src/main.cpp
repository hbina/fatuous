#include "akarin_database/glfw/akarin_glfw.hpp"
#include "processes/fatuous.hpp"
#include "akarin_imgui/akarin_imgui.hpp"

#include "entt/entt.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    // TODO :: People usually set up loggers here...
    // TODO :: Should databases be explicitly set up as well so as to not confuse people?
    Fatuous engine;
    engine.run();
    return 0;
};