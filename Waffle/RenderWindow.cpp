#include "RenderWindow.h"
#include <exception>

namespace waffle
{
	RenderWindow::RenderWindow(
		Context& context,
		std::wstring title,
		Rectangle size,
		WindowType type,
		MultiSampling sampleCount
	)
		: Window(title, size, type),
		context(context),
		swapChain(context, *this, sampleCount),
		depthStencilBuffer(context, &swapChain),
		rtv(context, &swapChain),
		dsv(context, &depthStencilBuffer)
	{
		// Resize resources when window resize event occurs.
		(void)resizeEvent.AddHandler([this](auto size) {
			// Resources using swapChain must be released before resize
			rtv.view.Reset();
			swapChain.Resize(size);
			depthStencilBuffer = Surface(this->context, &swapChain);
			rtv = RenderTargetView(this->context, &swapChain);
			dsv = DepthStencilView(this->context, &depthStencilBuffer);
		});
	}

	void RenderWindow::Clear(float r, float g, float b, float a, FLOAT depth, UINT8 stencil)
	{
		float color[4] = { r,g,b,a };
		context.DeviceContext()->ClearRenderTargetView(rtv.view.Get(), color);
		context.DeviceContext()->ClearDepthStencilView(dsv.view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
	}

    void RenderWindow::Set()
    {
		D3D11_VIEWPORT viewPort{};
		viewPort.Width = static_cast<float>(size.width);
		viewPort.Height = static_cast<float>(size.height);
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;

		context.DeviceContext()->RSSetViewports(1, &viewPort);
		context.DeviceContext()->OMSetRenderTargets(1, rtv.view.GetAddressOf(), dsv.view.Get());
    }

	void RenderWindow::Present()
	{
		swapChain.Present();
	}
}