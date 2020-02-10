#include "RenderSurface.h"
#include <exception>

namespace waffle
{
    RenderSurface::RenderSurface(Context& context, Rectangle size)
        : Surface(context, size), 
        context(context), 
        depthStencilBuffer(context, this),
        rtv(context, this),
        dsv(context, &depthStencilBuffer),
        srv(context, this)
    {}

    void RenderSurface::Clear(float r, float g, float b, float a, FLOAT depth, UINT8 stencil)
    {
        float color[4] = { r,g,b,a };
        context.DeviceContext()->ClearRenderTargetView(rtv.view.Get(), color);
        context.DeviceContext()->ClearDepthStencilView(dsv.view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
    }

    void RenderSurface::SetRT()
    {
        D3D11_VIEWPORT viewPort{};
        viewPort.Width = static_cast<float>(size.width);
        viewPort.Height = static_cast<float>(size.height);
        viewPort.MinDepth = 0.0f;
        viewPort.MaxDepth = 1.0f;

        context.DeviceContext()->RSSetViewports(1, &viewPort);
        context.DeviceContext()->OMSetRenderTargets(1, rtv.view.GetAddressOf(), dsv.view.Get());
    }

    void RenderSurface::SetVS(UINT slot)
    {
        context.DeviceContext()->VSSetShaderResources(slot, 1, srv.view.GetAddressOf());
    }

    void RenderSurface::SetPS(UINT slot)
    {
        context.DeviceContext()->PSSetShaderResources(slot, 1, srv.view.GetAddressOf());
    }
}
