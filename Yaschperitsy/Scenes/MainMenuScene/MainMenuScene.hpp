#pragma once

#include "App/Scene/Scene.hpp"
#include "GraphicEngine/ResourceManager/ResourceManager.hpp"
#include "Yaschperitsy/Entities/UILabel.hpp"

class MainMenuScene : public Scene
{
    public:
        MainMenuScene(const ResourceManager& rm,
                      const EventCallbackFn& callback, int win_width,
                      int win_height);

    private:
        const ResourceManager& rm_;
        int win_width_;
        int win_height_;
};
