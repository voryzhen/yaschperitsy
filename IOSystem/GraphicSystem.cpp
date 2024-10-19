#include "GraphicSystem.hpp"

#include "Logger/Logger.hpp"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Types.hpp"

#include <SDL_error.h>

constexpr int _sdl_img_flags { IMG_INIT_PNG | IMG_INIT_JPG };
constexpr int _sdl_flags { SDL_INIT_VIDEO };
constexpr std::string_view _sdl_hint_flags { SDL_HINT_RENDER_SCALE_QUALITY };

ErrorCode GraphicSystem::initialize()
{
    if (SDL_Init(_sdl_flags) < 0)
    {
        Logger().error("Couldn't initialize SDL. Error:");
        return ErrorCode::SDLInitError;
    }

    if (IMG_Init(_sdl_img_flags) < 0)
    {
        Logger().error("Couldn't initialize SDL Image. Error:");
        return ErrorCode::SDLImageInitError;
    }

    SDL_SetHint(_sdl_hint_flags.data(), "linear");

    if (TTF_Init() < 0)
    {
        Logger().error("Couldn't initialize SDL_ttf. Error:");
        return ErrorCode::SDLTTFInitError;
    }

    return ErrorCode::NoError;
}

ErrorCode GraphicSystem::finalize()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return ErrorCode::NoError;
}
