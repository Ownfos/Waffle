#include "ShaderBlob.h"

namespace waffle
{
    ShaderBlob::ShaderBlob(std::wstring relativePath)
    {
        try
        {
            static auto exePath = ExePath();
            auto fullPath = exePath + relativePath;

            if (FAILED(D3DReadFileToBlob(fullPath.c_str(), blob.GetAddressOf())))
                std::throw_with_nested(std::exception("Failed to read compiled shader object"));
        }
        catch (...)
        {
            std::throw_with_nested(std::exception("ShaderBlob::ShaderBlob()"));
        }
    }

    const void* ShaderBlob::Pointer()
    {
        return blob->GetBufferPointer();
    }

    SIZE_T ShaderBlob::Size()
    {
        return blob->GetBufferSize();
    }
}