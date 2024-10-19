#pragma once

#include <cstdint>

struct RenderData
{
        int x { 0 };
        int y { 0 };
        int w { 0 };
        int h { 0 };
        int id { 0 };
        float angle { 0.0 };
};

struct Color
{
        uint8_t r { 0 };
        uint8_t g { 0 };
        uint8_t b { 0 };
        uint8_t a { 0 };
};

enum class ErrorCode : uint8_t
{
    NoError = 0,
    SDLInitError,
    SDLImageInitError,
    SDLTTFInitError,
    SDLWindowCreationError,
    SDLRendererCreationError,
    TexturesFontsStorageInitError,
    TexturesFontsStoragefinalizeError,
    SDLRendererClearError,
    SDLRendererRenderError,
    IOSystemInitError,
    IOSystemFinalizeError,
};
