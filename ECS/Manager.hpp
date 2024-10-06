#pragma once

#include "Entity.hpp"
#include "Utility/Vector.hpp"
#include <algorithm>

class Manager
{
    public:
        void events();
        void update();
        void render(const Renderer& ren);
        void on_event(const EventSPtr& event);
        void add_entity(const EntityPtr& entity); // Add creator

        EntityArray get_entities() const { return entities_; }

        template <typename T>
        EntityArray get_entities() const
        {
            EntityArray res;
            std::ranges::copy_if(
                entities_, std::back_inserter(res), [&](const auto& entity)
                { return entity->get_typeID() == get_entity_typeID<T>(); });
            return res;
        }

        void refresh();

    private:
        EntityArray entities_;
};
using ManagerPtr = std::shared_ptr<Manager>;
