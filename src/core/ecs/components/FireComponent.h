#pragma once

#include "utility/Vector2D.h"
#include <core/ecs/IComponent.h>

namespace yaschperitsy::ecs::components
{

class FireComponent : public IComponent
{
    public:
        FireComponent() = default;
        FireComponent(std::int8_t reload) : _reload(reload) {};

        void update(const SDL_Event& /*e*/) override
        {
            if (_reloading > 0)
            {
                _reloading--;
            }
        }

        void init() override {}

        void render(const core::SDL_RendererUPtr& renderer) override {}

        bool reloaded() const { return _reloading == 0; }

        void shot() { _reloading = _reload; }

    private:
        std::int8_t _reload{8};
        std::int8_t _reloading{8};
};

}; // namespace yaschperitsy::ecs::components
