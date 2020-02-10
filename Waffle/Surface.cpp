#include "Surface.h"
#include <exception>

namespace waffle
{
	Surface::Surface(
		Context& context,
		DXGI_FORMAT format,
		UINT bindFlags,
		Rectangle size,
		MultiSampling sampleCount
	)
		: size(size), sampleCount(sampleCount)
	{
		try
		{
			D3D11_TEXTURE2D_DESC desc{};
			desc.BindFlags = bindFlags;
			desc.Format = format;
			desc.Width = size.width;
			desc.Height = size.height;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.SampleDesc.Count = static_cast<int>(sampleCount);
			desc.SampleDesc.Quality = 0;

			if (FAILED(context.Device()->CreateTexture2D(&desc, nullptr, texture.GetAddressOf())))
				throw std::exception("Failed to create texture 2d");
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("Surface::Surface()"));
		}
	}

	// Depth stencil buffer for render target buffer
	Surface::Surface(
		Context& context,
		ITextureResource* renderTargetBuffer
	)
		: Surface(
			context,
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			D3D11_BIND_DEPTH_STENCIL,
			renderTargetBuffer->Size(),
			renderTargetBuffer->SampleCount()
		)
	{}

	// Buffer used as render target & shader resource
	Surface::Surface(
		Context& context,
		Rectangle size
	)
		: Surface(
			context,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,
			size,
			MultiSampling::None
		)
	{}

	ID3D11Texture2D* Surface::Texture()
	{
		return texture.Get();
	}

	Rectangle Surface::Size()
	{
		return size;
	}

	MultiSampling Surface::SampleCount()
	{
		return sampleCount;
	}
}