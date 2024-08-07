#pragma once

#include <memory>
#include <string_view>

#include "SDL_render.h"
#include "core/events/Event.hpp"
#include "core/renderer/Renderer.hpp"

namespace yaschperitsy::core
{

class Layer
{
    public:
        Layer(const std::string_view& name = "Layer") : _name(name) {}

        virtual ~Layer() = default;

        virtual void on_attach() {}

        virtual void on_detach() {}

        virtual void update() {}

        virtual void render(const renderer::SDLRendererUPtr&) {}

        virtual void on_event(const events::EventSPtr& event) {}

        std::string_view name() const { return _name; }

    protected:
        std::string_view _name;
};

using LayerUPtr = std::unique_ptr<Layer>;
using LayerSPtr = std::shared_ptr<Layer>;

}; // namespace yaschperitsy::core
