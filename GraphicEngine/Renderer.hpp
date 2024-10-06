#pragma once

#include "RendererImpl/IRendererImpl.hpp"
#include "Types.hpp"
#include <utility>

class Renderer
{
    public:
        static Renderer& get();

        ErrorCode initialize() const;
        ErrorCode finalize() const;

        ErrorCode clear() const;
        ErrorCode render(const RenderData& data) const;
        ErrorCode present() const;

        std::pair<int, int> get_window_size() const;

    private:
        Renderer();
        IRendererImplPtr _impl;
};
