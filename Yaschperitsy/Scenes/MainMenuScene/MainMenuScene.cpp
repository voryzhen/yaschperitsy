#include "MainMenuScene.hpp"

#include "Entities/UILabel.hpp"
#include "Yaschperitsy/Style.hpp"

MainMenuScene::MainMenuScene(const ResourceManager& rm,
                             const EventCallbackFn& callback, int win_width,
                             int win_height)
    : rm_(rm), win_width_(win_width), win_height_(win_height)
{
    std::array<RenderData, 3> text1_textures = {
        rm_.load_texture("New Game", grey), rm_.load_texture("New Game", green),
        rm_.load_texture("New Game", blue)
    };
    EntityPtr text1 = UIButton::create(UIEventCode::NewGame, win_width_, 80,
                                       text1_textures, callback);

    std::array<RenderData, 3> text2_textures = {
        rm_.load_texture("Settings", grey), rm_.load_texture("Settings", green),
        rm_.load_texture("Settings", blue)
    };
    EntityPtr text2 = UIButton::create(UIEventCode::Settings, win_width_, 140,
                                       text2_textures, callback);

    std::array<RenderData, 3> text3_textures = {
        rm_.load_texture("Exit", grey), rm_.load_texture("Exit", green),
        rm_.load_texture("Exit", blue)
    };
    EntityPtr text3 = UIButton::create(UIEventCode::Exit, win_width_, 200,
                                       text3_textures, callback);

    man_->add_entity(text1);
    man_->add_entity(text2);
    man_->add_entity(text3);
}