#pragma once

#include "ECS/Components/SpriteComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "GraphicEngine/ResourceManager/ResourceManager.hpp"
#include "GraphicEngine/Types.hpp"
#include "Scenes/GameScene/Controllers/Controller.hpp"
#include "Scenes/GameScene/GameSettings.hpp"
#include "styleYaml.hpp"
#include <memory>
#include <string>

const static auto* bg_asset = "Assets/background.png";

class UIController : public Controller
{
    public:
        UIController(ManagerPtr& man, const ResourceManager& rm,
                     GameInfo& game_info, int win_width, int win_height)
            : man_(man), rm_(rm), game_info_(game_info)
        {

            // Init text
            hp_ = std::make_shared<Entity>();
            hp_->add_component<TransformComponent>(30, 10);
            hp_rd_ = rm_.load_texture(
                std::string { "HP " } +
                    std::to_string(game_info_.statistics_._curr_hp),
                lightgrey);
            hp_->add_component<SpriteComponent>(hp_rd_);

            score_ = std::make_shared<Entity>();
            score_->add_component<TransformComponent>(230, 10);
            score_rd_ = rm_.load_texture(
                std::string { "Score " } +
                    std::to_string(game_info_.statistics_._score),
                lightgrey);
            score_->add_component<SpriteComponent>(score_rd_);

            remaining_ = std::make_shared<Entity>();
            remaining_->add_component<TransformComponent>(430, 10);
            remaining_rd_ = rm_.load_texture(
                std::string { "Remaining Yaschs " } +
                    std::to_string(game_info_.statistics_._yaschperitsy_num),
                lightgrey);
            remaining_->add_component<SpriteComponent>(remaining_rd_);

            // Init Background
            EntityPtr background = std::make_shared<Entity>();
            background->add_component<TransformComponent>(0, 0);
            auto bg_render_data = rm_.load_texture(bg_asset);
            bg_render_data.w = win_width;
            bg_render_data.h = win_height;
            background->add_component<SpriteComponent>(bg_render_data);
            man_->add_entity(background);

            man_->add_entity(hp_);
            man_->add_entity(score_);
            man_->add_entity(remaining_);
        }

        void update() override
        {
            auto hp_rd = rm_.update_texture(
                hp_rd_.id,
                std::string { "Score " } +
                    std::to_string(game_info_.statistics_._curr_hp),
                lightgrey);
            hp_rd.x = 30;
            hp_rd.y = 10;
            hp_->get_component<SpriteComponent>()->set_render_data(hp_rd);

            auto new_score_rd = rm_.update_texture(
                score_rd_.id,
                std::string { "Score " } +
                    std::to_string(game_info_.statistics_._score),
                lightgrey);
            new_score_rd.x = 230;
            new_score_rd.y = 10;
            score_->get_component<SpriteComponent>()->set_render_data(
                new_score_rd);

            auto new_remaining_rd = rm_.update_texture(
                remaining_rd_.id,
                std::string { "Remaining Yaschs " } +
                    std::to_string(game_info_.statistics_._yaschperitsy_num),
                lightgrey);
            new_remaining_rd.x = 430;
            new_remaining_rd.y = 10;
            remaining_->get_component<SpriteComponent>()->set_render_data(
                new_remaining_rd);
        }

    private:
        ManagerPtr& man_;
        const ResourceManager& rm_;
        GameInfo& game_info_;

        EntityPtr hp_;
        EntityPtr score_;
        EntityPtr remaining_;

        RenderData hp_rd_;
        RenderData score_rd_;
        RenderData remaining_rd_;
};
using UIControllerPtr = std::shared_ptr<UIController>;
