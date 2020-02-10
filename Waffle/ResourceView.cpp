#include "ResourceView.h"
#include <exception>

namespace waffle
{
	RenderTargetView::RenderTargetView(Context& context, ITextureResource* resource)
	{
		if (FAILED(context.Device()->CreateRenderTargetView(resource->Texture(), nullptr, view.GetAddressOf())))
			throw std::exception("Failed to create render target view");
	}


	DepthStencilView::DepthStencilView(Context& context, ITextureResource* resource)
	{
		if (FAILED(context.Device()->CreateDepthStencilView(resource->Texture(), nullptr, view.GetAddressOf())))
			throw std::exception("Failed to create depth stencil view");
	}

    ShaderResourceView::ShaderResourceView(Context& context, ITextureResource* resource)
    {
		if (FAILED(context.Device()->CreateShaderResourceView(resource->Texture(), nullptr, view.GetAddressOf())))
			throw std::exception("Failed to create shader resource view");
    }
}