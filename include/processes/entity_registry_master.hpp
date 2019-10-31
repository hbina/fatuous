#ifndef ENTITY_SYSTEM_MASTER_HPP
#define ENTITY_SYSTEM_MASTER_HPP

#include <cstddef>

namespace EntityRegistryMaster
{
void create_entity(const int) noexcept;
void run() noexcept;
int get_entity_count() noexcept;
}; // namespace EntityRegistryMaster

#endif