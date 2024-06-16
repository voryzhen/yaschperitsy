#pragma once

#include <algorithm>
#include <ecs/entity.h>

namespace yaschperitsy::ecs
{

class Manager
{
    public:
        void update(const SDL_Event& event)
        {
            for (auto& e : _entities)
            {
                e->update(event);
            }
        }

        void render(const app::SDL_RendererUPtr& renderer)
        {
            for (auto& e : _entities)
            {
                e->render(renderer);
            }
        }

        void refresh()
        {
            const auto& remove_it = std::remove_if(
                _entities.begin(), _entities.end(),
                [](const auto& e) { return !e->is_active(); });

            _entities.erase(remove_it, _entities.end());
        }

        EntitySPtr add_entity(const std::string_view& name = "")
        {
            _entities.emplace_back(new Entity(name));
            return _entities.back();
        }

        const SEntityVector& get_entities() const { return _entities; }

        SEntityVector get_entities_by_name(const std::string& name)
        {
            SEntityVector res;
            std::copy_if(_entities.begin(), _entities.end(),
                         std::back_inserter(res),
                         [&](const EntitySPtr& e)
                         { return e->name() == name; });
            return res;
        }

    private:
        SEntityVector _entities;
};

}; // namespace yaschperitsy::ecs
