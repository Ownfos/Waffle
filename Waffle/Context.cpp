#include "Context.h"
#include <exception>

namespace waffle
{
    Context::Context()
    {
		try
		{
			if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(factory.GetAddressOf()))))
				throw std::exception("Failed to create factory");

#ifdef _DEBUG
			UINT deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
			UINT deviceFlags = NULL;
#endif
			D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1 };

			// Try creating device with adapters
			auto succeeded = [this, deviceFlags, featureLevels]
			{
				ComPtr<IDXGIAdapter1> adapter;
				for (auto i = 0U; factory->EnumAdapters1(i, adapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND; ++i)
				{
					if (SUCCEEDED(D3D11CreateDevice(
						adapter.Get(),
						D3D_DRIVER_TYPE_UNKNOWN,
						NULL,
						deviceFlags,
						featureLevels,
						ARRAYSIZE(featureLevels),
						D3D11_SDK_VERSION,
						device.GetAddressOf(),
						NULL,
						deviceContext.GetAddressOf())))
					{
						return true;
					}
				}
				return false;
			}();
			if (!succeeded)
				throw std::exception("Failed to create device");

#ifdef _DEBUG
			if (FAILED(device->QueryInterface(IID_PPV_ARGS(debug.GetAddressOf()))))
				throw std::exception("Failed to query debug layer from device");
#endif
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("GraphicContext::GraphicContext()"));
		}
    }

    IDXGIFactory1* Context::Factory()
    {
        return factory.Get();
    }

    ID3D11Device* Context::Device()
	{
		return device.Get();
	}

	ID3D11DeviceContext* Context::DeviceContext()
	{
		return deviceContext.Get();
	}

    void Context::UnbindVSResource(UINT slot)
    {
		ID3D11ShaderResourceView* nullView = nullptr;
		deviceContext->VSSetShaderResources(slot, 1, &nullView);
    }

	void Context::UnbindPSResource(UINT slot)
	{
		ID3D11ShaderResourceView* nullView = nullptr;
		deviceContext->PSSetShaderResources(slot, 1, &nullView);
	}
}