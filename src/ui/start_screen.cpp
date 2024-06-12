#include "ui/start_screen.h"
#include "ui/button.h"
#include <memory>

StartScreen::StartScreen(TTF_FontSPtr font,
                         const SDL_RendererSPtr& _renderer)
    : _font(std::move(font)), _renderer(_renderer)
{
    btns.emplace_back(std::make_unique<Button>("New Game", _font,
                                               _renderer, 100, 100));

    btns[0]->add_on_click_listeners(
        []()
        { std::cout << "outer listener for new game" << std::endl; });

    btns.emplace_back(std::make_unique<Button>("Settings", _font,
                                               _renderer, 100, 150));

    btns[1]->add_on_click_listeners(
        []()
        { std::cout << "outer listener for Settings" << std::endl; });

    btns.emplace_back(
        std::make_unique<Button>("Exit", _font, _renderer, 100, 200));

    btns[2]->add_on_click_listeners(
        []() { std::cout << "outer listener for Exit" << std::endl; });
};

StartScreen::~StartScreen() {}

void StartScreen::update(const SDL_Event& event)
{
    for (auto& btn : btns)
    {
        btn->update(event);
    }
}

void StartScreen::render()
{
    for (auto& btn : btns)
    {
        btn->render();
    }
}
