#include "PixelShader.h"

namespace waffle
{
    PixelShader::PixelShader(Context& context, ShaderBlob&& blob)
        : context(context), blob(std::move(blob))
    {
        try
        {
            if (FAILED(context.Device()->CreatePixelShader(
                this->blob.Pointer(),
                this->blob.Size(),
                nullptr,
                shader.GetAddressOf())))
            {
                throw std::exception("Failed to create pixel shader");
            }
        }
        catch (...)
        {
            std::throw_with_nested(std::exception("PixelShader::PixelShader()"));
        }
    }

    void PixelShader::Set()
    {
        context.DeviceContext()->PSSetShader(shader.Get(), nullptr, 0);
    }
}