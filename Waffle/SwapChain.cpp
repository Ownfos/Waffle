#include "SwapChain.h"

namespace waffle
{
	SwapChain::SwapChain(
		Context& context,
		const Window& window,
		MultiSampling sampleCount
	)
		: size(window.Size()), sampleCount(sampleCount)
	{
		try
		{
			DXGI_SWAP_CHAIN_DESC desc = {};
			{
				desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				desc.BufferDesc.RefreshRate.Numerator = 60;
				desc.BufferDesc.RefreshRate.Denominator = 1;
				desc.BufferCount = 2;
				desc.BufferDesc.Width = size.width;
				desc.BufferDesc.Height = size.height;
				desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
				desc.OutputWindow = window.Handle();
				desc.SampleDesc.Count = static_cast<int>(sampleCount);
				desc.SampleDesc.Quality = 0;
				desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
				desc.Windowed = true;
			}

			if (FAILED(context.Factory()->CreateSwapChain(context.Device(), &desc, swapChain.GetAddressOf())))
				throw std::exception("Failed to create swap chain");

			if (FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()))))
				throw std::exception("Failed to get back buffer");
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("SwapChain::SwapChain()"));
		}
	}

	SwapChain::~SwapChain()
	{
		if (swapChain)
			swapChain->SetFullscreenState(false, NULL);
	}

	void SwapChain::Present()
	{
		swapChain->Present(0, 0);
	}

	void SwapChain::SetFullScreen(bool enable)
	{
		swapChain->SetFullscreenState(enable, nullptr);
	}

	void SwapChain::Resize(Rectangle size)
	{
		try
		{
			this->size = size;

			backBuffer.Reset();

			if (FAILED(swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0)))
				throw std::exception("Failed to resize swap chain");

			if (FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()))))
				throw std::exception("Failed to get back buffer");
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("SwapChain::Resize()"));
		}
	}

    ID3D11Texture2D* SwapChain::Texture()
    {
        return backBuffer.Get();
    }
	Rectangle SwapChain::Size()
	{
		return size;
	}

	MultiSampling SwapChain::SampleCount()
	{
		return sampleCount;
	}
}