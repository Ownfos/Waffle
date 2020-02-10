#include "InputLayout.h"

#include "ShaderBlob.h"
#include "InputElement.h"
#include <vector>

namespace waffle
{
    InputLayout::InputLayout(
        Context& context, 
        ShaderBlob& blob, 
        std::vector<InputElement> elements
    )
        : elements(elements)
    {
        auto offset = 0U;
        std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc{};
        for (auto& element : elements)
        {
            D3D11_INPUT_ELEMENT_DESC desc{};
            desc.AlignedByteOffset = offset;
            desc.Format = element.Format();
            desc.SemanticName = element.Name();
            desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

            elementDesc.push_back(desc);
            offset += element.Size();
        }

        if (FAILED(context.Device()->CreateInputLayout(
            &elementDesc[0],
            elementDesc.size(),
            blob.Pointer(),
            blob.Size(),
            layout.GetAddressOf())))
        {
            throw std::exception("Failed to create input layout");
        }
    }

    ID3D11InputLayout* InputLayout::Get()
    {
        return layout.Get();
    }
}