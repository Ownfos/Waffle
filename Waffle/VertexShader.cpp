#include "VertexShader.h"

namespace waffle
{
    VertexShader::VertexShader(
        Context& context,
        ShaderBlob&& blob,
        std::vector<InputElement> elements
    )
        : context(context), blob(std::move(blob)), layout(context, this->blob, elements)
    {
        try
        {
            if (FAILED(context.Device()->CreateVertexShader(
                this->blob.Pointer(),
                this->blob.Size(),
                nullptr,
                shader.GetAddressOf())))
            {
                throw std::exception("Failed to create vertex shader");
            }
        }
        catch (...)
        {
            std::throw_with_nested(std::exception("VertexShader::VertexShader()"));
        }
    }

    void VertexShader::Set()
    {
        context.DeviceContext()->IASetInputLayout(layout.Get());
        context.DeviceContext()->VSSetShader(shader.Get(), nullptr, 0);
    }
}