#include "akarin_database/lighting/lighting_database.hpp"

LightingDatabase &LightingDatabase::get_instance() noexcept
{
    static LightingDatabase instance;
    return instance;
}