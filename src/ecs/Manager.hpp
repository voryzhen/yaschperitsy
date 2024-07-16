#pragma once

#include <algorithm>
#include <ecs/Entity.hpp>
#include <ecs/EntityCreator.hpp>
#include <iterator>

namespace yaschperitsy::ecs
{

class Manager
{
    public:
        void update(const SDL_Event& event)
        {
            std::for_each(_entities.begin(), _entities.end(),
                          [&](auto& e) { e->update(event); });
        }

        void render(const core::renderer::SDLRendererUPtr& renderer)
        {
            std::for_each(_entities.begin(), _entities.end(),
                          [&](auto& e) { e->render(renderer); });
        }

        void refresh()
        {
            const auto& remove_it =
                std::remove_if(_entities.begin(), _entities.end(),
                               [](const auto& e) { return !e->is_active(); });

            _entities.erase(remove_it, _entities.end());
        }

        template <typename EntityClass, typename EntitySettings>
        EntitySPtr add_entity(EntitySettings settings, float x_pox, float y_pox,
                              int speed,
                              const core::resources::TextureSPtr& texture)
        {
            _entities.emplace_back(EntityCreator::create_entity<EntityClass>(
                settings, x_pox, y_pox, speed, texture));

            return _entities.back();
        }

        const SEntityVector& get_entities() const { return _entities; }

        SEntityVector get_entities(EntityType type)
        {
            SEntityVector res;
            std::copy_if(_entities.begin(), _entities.end(),
                         std::back_inserter(res), [&](const EntitySPtr& e)
                         { return e->type() == type; });
            return res;
        }

    private:
        SEntityVector _entities;
};

}; // namespace yaschperitsy::ecs
