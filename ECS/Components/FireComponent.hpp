#pragma once

#include "Component.hpp"
#include <memory>

class FireComponent : public Component
{
    public:
        FireComponent() = default;
        explicit FireComponent(std::uint8_t reload)
            : reload_(reload), reloading_(reload) {};

        void events() override {};

        void update() override
        {
            if (reloading_ > 0)
            {
                reloading_--;
            }
        };

        void render(const Renderer& ren) override {};

        void on_event() override {};

        void init() override {};

        bool reloaded() const { return reloading_ == 0; }

        void shot() { reloading_ = reload_; }

    private:
        std::uint8_t reload_ { 120 };
        std::uint8_t reloading_ { 120 };
};
using FireComponentPtr = std::shared_ptr<FireComponent>;
