#include "TypesID.hpp"

//=== Component utils ===//

ComponentTypeID init_component_typeID()
{
    static ComponentTypeID component_type_id { 0 };
    return component_type_id++;
}

//=== Entity utils ===//

EntityTypeID init_entity_typeID()
{
    static EntityTypeID entity_type_id { 0 };
    return entity_type_id++;
}
