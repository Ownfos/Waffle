#include "InputElement.h"

namespace waffle
{
    InputElement::InputElement(std::string semanticName, InputFormat format)
        : semanticName(semanticName)
    {
        try
        {
            switch (format)
            {
                case InputFormat::Float2:
                {
                    this->format = DXGI_FORMAT_R32G32_FLOAT;
                    bytesPerPixel = 8;
                    break;
                }
                case InputFormat::Float3:
                {
                    this->format = DXGI_FORMAT_R32G32B32_FLOAT;
                    bytesPerPixel = 12;
                    break;
                }
                case InputFormat::Float4:
                {
                    this->format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    bytesPerPixel = 16;
                    break;
                }
                default:
                {
                    throw std::exception("Invalid input format");
                }
            }
        }
        catch (...)
        {
            std::throw_with_nested(std::exception("InputElement::InputElement()"));
        }
    }

    const char* InputElement::Name()
    {
        return semanticName.c_str();
    }

    DXGI_FORMAT InputElement::Format()
    {
        return format;
    }

    UINT InputElement::Size()
    {
        return bytesPerPixel;
    }
}