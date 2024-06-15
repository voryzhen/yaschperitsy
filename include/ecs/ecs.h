#pragma once

#include "SDL_events.h"
#include "SDL_render.h"
#include "ecs/components.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace yaschperitsy::app
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

        void render(const SDL_RendererUPtr& renderer)
        {
            for (auto& e : _entities)
            {
                e->render(renderer);
            }
        }

        void refresh()
        {
            _entities.erase(std::remove_if(_entities.begin(),
                                           _entities.end(),
                                           [](const auto& e)
                                           { return !e->is_active(); }),
                            _entities.end());
        }

        Entity& add_entity(const std::string_view& name = "")
        {
            auto e = new Entity(name);
            std::unique_ptr<Entity> u_e(e);
            _entities.emplace_back(std::move(u_e));
            return *e;
        }

        std::vector<Entity*>
        get_entities_by_name(const std::string& name)
        {
            std::vector<Entity*> res;
            for (const auto& e : _entities)
            {
                if (e->_name == name)
                {
                    res.push_back(e.get());
                }
            }
            return res;
        }

        std::vector<Entity*> get_entities()
        {
            std::vector<Entity*> res;
            res.reserve(_entities.size());
            for (const auto& e : _entities)
            {
                res.push_back(e.get());
            }
            return res;
        }

    private:
        std::vector<std::unique_ptr<Entity>> _entities;
};

}; // namespace yaschperitsy::app
