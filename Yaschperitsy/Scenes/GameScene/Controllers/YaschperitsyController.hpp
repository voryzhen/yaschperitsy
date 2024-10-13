#pragma once

#include "ECS/Manager.hpp"
#include "GraphicEngine/ResourceManager/ResourceManager.hpp"
#include "GraphicEngine/Types.hpp"
#include "Scenes/GameScene/Controllers/Controller.hpp"
#include "Scenes/GameScene/GameSettings.hpp"
#include <memory>

const static auto* yaschperitsa_asset_1 =
    "Assets/Yaschperitsy/yaschperitsa_1.png";
const static auto* yaschperitsa_asset_2 =
    "Assets/Yaschperitsy/yaschperitsa_2.png";
const static auto* yaschperitsa_fireball_asset =
    "Assets/Yaschperitsy/yaschperitsy_fireball.png";

class YaschperitsyController : public Controller
{
    public:
        YaschperitsyController(ManagerPtr& man, const ResourceManager& rm,
                               GameInfo& game_info, int win_width,
                               int win_height)
            : man_(man), rm_(rm), game_info_(game_info), win_width_(win_width),
              win_height_(win_height)
        {
            yaschperitsa_1_ = rm_.load_texture(yaschperitsa_asset_1);
            yaschperitsa_2_ = rm_.load_texture(yaschperitsa_asset_2);
            yaschperitsa_fireball_ =
                rm_.load_texture(yaschperitsa_fireball_asset);
        }

        void spawn_yaschperitsy();
        void update() override;
        void update_direction();
        void fire();

    private:
        ManagerPtr& man_;
        const ResourceManager& rm_;
        GameInfo& game_info_;

        int win_width_ { 0 };
        int win_height_ { 0 };

        int yaschperitsy_spawn_timer_ { 0 };

        RenderData yaschperitsa_1_;
        RenderData yaschperitsa_2_;
        RenderData yaschperitsa_fireball_;
};
using YaschperitsyControllerPtr = std::shared_ptr<YaschperitsyController>;
