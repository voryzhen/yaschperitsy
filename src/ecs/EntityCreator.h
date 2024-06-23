#pragma once

#include "app/ResourceManager.h"
#include "game/entities/Ammunition.h"
#include "game/entities/Organism.h"
#include <ecs/Entity.h>
#include <memory>
#include <utility>

namespace yaschperitsy::ecs
{

class EntityCreator
{
    public:
        template <typename T, typename Type, typename... TArgs>
        static EntitySPtr create_entity(Type type, TArgs&&... args)
        {
            auto entity = std::shared_ptr<T>(new T(type));

            int args_size = sizeof...(args);
            if (args_size > 0)
            {
                init_components(entity, std::forward<TArgs>(args)...);
            }

            return entity;
        }

    private:
        static void init_components(EntitySPtr entity, float x_pox,
                                    float y_pox, int speed,
                                    resource::TextureSPtr texture);
        static void init_yaschperitsa_components(EntitySPtr& entity);
        static void init_player_components(EntitySPtr& entity);
        static void init_ammunition_components(EntitySPtr& entity);
};

}; // namespace yaschperitsy::ecs
