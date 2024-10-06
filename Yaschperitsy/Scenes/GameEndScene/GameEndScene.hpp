#pragma once

#include "GameEngine/Scene/Scene.hpp"
#include "GraphicEngine/ResourceManager/ResourceManager.hpp"
#include "Yaschperitsy/Entities/UILabel.hpp"

class GameEndScene : public Scene
{
    public:
        GameEndScene(const ResourceManager& rm, const EventCallbackFn& callback,
                     int win_width, int win_height);

    private:
        const ResourceManager& rm_;
        int win_width_;
        int win_height_;
};
