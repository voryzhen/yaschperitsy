#pragma once

#include <cstdint>

//=== Component utils ===//

using ComponentTypeID = std::uint8_t;

ComponentTypeID init_component_typeID();

template <typename T>
ComponentTypeID get_component_typeID()
{
    static ComponentTypeID _typeID = init_component_typeID();
    return _typeID;
}

//=== Entity utils ===//

using EntityTypeID = std::uint8_t;

EntityTypeID init_entity_typeID();

template <typename T>
EntityTypeID get_entity_typeID()
{
    static EntityTypeID _typeID = init_entity_typeID();
    return _typeID;
}
