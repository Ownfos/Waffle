#include "Sampler.h"
#include <exception>

namespace waffle
{
    Sampler::Sampler(Context& context, D3D11_TEXTURE_ADDRESS_MODE mode)
        : context(context)
    {
		try
		{
			D3D11_SAMPLER_DESC desc{};
			desc.AddressU = desc.AddressV = desc.AddressW = mode;
			desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			desc.MinLOD = 0;
			desc.MaxLOD = D3D11_FLOAT32_MAX;
			if (FAILED(context.Device()->CreateSamplerState(&desc, sampler.GetAddressOf())))
				throw std::exception("Failed to create sampler state");
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("Sampler::Sampler"));
		}
    }

	void Sampler::SetVS(UINT slot)
	{
		context.DeviceContext()->VSSetSamplers(slot, 1, sampler.GetAddressOf());
	}

	void Sampler::SetPS(UINT slot)
	{
		context.DeviceContext()->PSSetSamplers(slot, 1, sampler.GetAddressOf());
	}
}