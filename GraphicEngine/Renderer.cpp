#include "Renderer.hpp"

#include "GraphicEngine/RendererImpl/IRendererImpl.hpp"

Renderer& Renderer::get()
{
    static Renderer singleton;
    return singleton;
}

ErrorCode Renderer::initialize() const { return _impl->initialize(); }
ErrorCode Renderer::finalize() const { return _impl->finalize(); }

ErrorCode Renderer::clear() const { return _impl->clear(); }

ErrorCode Renderer::render(const RenderData& data) const
{
    return _impl->render(data);
}

ErrorCode Renderer::present() const { return _impl->present(); }

Renderer::Renderer() : _impl(get_renderer_impl()) {}

std::pair<int, int> Renderer::get_window_size() const
{
    return _impl->get_window_size();
};
