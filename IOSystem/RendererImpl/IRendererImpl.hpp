#pragma once

#include "IOSystem/Types.hpp"
#include <memory>

class IRendererImpl
{
    public:
        virtual ~IRendererImpl() = default;
        virtual ErrorCode initialize() = 0;
        virtual ErrorCode finalize() = 0;

        // Render Interface
        virtual ErrorCode clear() const = 0;
        virtual ErrorCode render(const RenderData& data) const = 0;
        virtual ErrorCode present() const = 0;

        virtual std::pair<int, int> get_window_size() const = 0;
};
using IRendererImplPtr = std::shared_ptr<IRendererImpl>;

IRendererImplPtr get_renderer_impl();
