#pragma once

#include "SDL_events.h"
#include <memory>
#include <resource_manager.h>

class BaseScreen
{
    public:
        BaseScreen(const ResourceManagerUPtr& rm, int* current_screen);
        virtual ~BaseScreen();
        virtual void update();
        virtual void render(const SDL_RendererUPtr& _renderer);
        virtual void handle_events(const SDL_Event& event);

    protected:
        int* _current_screen{nullptr};
        const ResourceManagerUPtr& _rm;
};

using BaseScreenUPtr = std::unique_ptr<BaseScreen>;