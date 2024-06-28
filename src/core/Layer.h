#pragma once

#include "core/Logger.h"
#include "core/events/Event.h"
#include <memory>
#include <string_view>

namespace yaschperitsy::core
{

class Layer
{
    public:
        Layer(const std::string_view& name = "Layer") : _name(name) {}

        virtual ~Layer() {}

        virtual void on_attach() {}

        virtual void on_detach() {}

        virtual void on_update() {}

        virtual void on_event(const events::EventSPtr& event) {}

        std::string_view name() const { return _name; }

    protected:
        std::string_view _name;
};

using LayerUPtr = std::unique_ptr<Layer>;
using LayerSPtr = std::shared_ptr<Layer>;

}; // namespace yaschperitsy::core
