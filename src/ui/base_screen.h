#pragma once

#include "SDL_events.h"
#include <app/resource_manager.h>
#include <memory>

namespace yaschperitsy::ui
{

class BaseScreen
{
    public:
        BaseScreen(const resource::ResourceManagerUPtr& rm,
                   int* current_screen);
        virtual ~BaseScreen();
        virtual void update();
        virtual void
        render(const resource::SDL_RendererUPtr& _renderer);
        virtual void handle_events(const SDL_Event& event);

    protected:
        int* _current_screen{nullptr};
        const resource::ResourceManagerUPtr& _rm;
};

using BaseScreenUPtr = std::unique_ptr<BaseScreen>;

}; // namespace yaschperitsy::ui
