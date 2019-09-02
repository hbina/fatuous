#ifndef ENTITY_SYSTEM_MASTER_HPP
#define ENTITY_SYSTEM_MASTER_HPP

#include <cstddef>

namespace EntityRegistryMaster
{
void create_entity(const std::size_t) noexcept;
void run(const float) noexcept;
std::size_t get_entity_count() noexcept;
}; // namespace EntityRegistryMaster

#endif