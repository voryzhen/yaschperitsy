#pragma once

#include <ecs2/icomponent.h>

namespace yaschperitsy::ecs2::components
{

class FireComponent : public IComponent
{
    public:
        FireComponent() = default;
        FireComponent(std::int8_t reload) : _reload(reload) {};

        void update(const SDL_Event& /*e*/) override
        {
            if (_curr_load > 0)
            {
                _curr_load--;
            }
        }

        void init() override {}

        void render(const app::SDL_RendererUPtr& renderer) override {}

        bool is_reloaded() const { return _curr_load == 0; }

        void shot() { _curr_load = _reload; }

    private:
        std::int8_t _reload{8};
        std::int8_t _curr_load{8};
};

}; // namespace yaschperitsy::ecs2::components
