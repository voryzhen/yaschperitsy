#pragma once

#include "Types.hpp"
#include <SDL_render.h>
#include <memory>

class IStorageGetter
{
    public:
        virtual ~IStorageGetter() = default;
        virtual SDL_Texture* get_texture(int id) = 0;
        virtual ErrorCode finalize() = 0;
};
using IStorageGetterPtr = std::shared_ptr<IStorageGetter>;

IStorageGetterPtr get_storage_getter();
