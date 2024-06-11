#include "ui/menu.h"

void Menu::show_menu()
{
    while (!_quit)
    {
        handle_events();
        update();
        render();
    }
}

void Menu::render()
{
    SDL_RenderClear(_renderer.get());
    SDL_SetRenderDrawColor(_renderer.get(), 92, 92, 122, 255);

    // render_menu();
    // TODO: very very bad = rewrite
    for (auto& btn : btns)
    {
        SDL_RenderCopy(_renderer.get(), btn._texture->_texture, NULL,
                       &btn.drect);
    }

    SDL_RenderPresent(_renderer.get());
}

void Menu::render_menu()
{
    int i = 0;
    for (const auto& item : _menu_items)
    {
        render_text(_renderer, item.data(), 100, 100 + 40 * i);
        i++;
    }
}

// TODO: make common
void Menu::render_text(const SDL_RendererPtr& renderer,
                       const std::string& text, int x, int y)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(
        _rm->get_font("lazy").get(), text.c_str(), _text_color);

    SDL_Texture* text_texture{nullptr};

    int w = 0;
    int h = 0;

    if (text_surface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: "
               "%s\n",
               TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        text_texture =
            SDL_CreateTextureFromSurface(renderer.get(), text_surface);
        if (text_texture == nullptr)
        {
            printf("Unable to create texture from rendered "
                   "text! SDL "
                   "Error: %s\n",
                   SDL_GetError());
        }
        else
        {
            // Get image dimensions
            w = text_surface->w;
            h = text_surface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(text_surface);
    }

    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer.get(), text_texture, NULL, &rect);
}

void Menu::handle_events()
{
    SDL_PollEvent(&_event);
    switch (_event.type)
    {
    case SDL_QUIT:
        _quit = true;
        break;

    default:
        break;
    }
}

void Menu::update()
{

    for (auto& btn : btns)
    {
        btn.update();
    }
}
