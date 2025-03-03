#include "Shader.h"

HRESULT Shader::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

Shader::Shader(const WCHAR* shaderFile, D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize, ID3D11DeviceContext* context, ID3D11Device* device)
{
    // Blobs for Vertex and Pixel Shader Blobs
    ID3DBlob* t_VSBlob = nullptr;
    ID3DBlob* t_PSBlob = nullptr;

    HRESULT t_HR = CompileShaderFromFile(shaderFile, "VS", "vs_4_0", &t_VSBlob);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
    }

    t_HR = device->CreateVertexShader(t_VSBlob->GetBufferPointer(), t_VSBlob->GetBufferSize(), nullptr, &m_VertexShader);
    if (FAILED(t_HR)) 
    { 

        t_VSBlob->Release(); 
    }

    UINT t_NumOfElements = layoutSize;

    t_HR = device->CreateInputLayout(layout, t_NumOfElements, t_VSBlob->GetBufferPointer(), t_VSBlob->GetBufferSize(), &m_VertexLayout);
    t_VSBlob->Release();
    if (FAILED(t_HR))
    {

    }

    t_HR = CompileShaderFromFile(shaderFile, "PS", "ps_4_0", &t_PSBlob);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
    }

    t_HR = device->CreatePixelShader(t_PSBlob->GetBufferPointer(), t_PSBlob->GetBufferSize(), nullptr, &m_PixelShader);
    t_PSBlob->Release();
    if (FAILED(t_HR))
    {

    }
}

Shader::~Shader()
{
    if (m_VertexLayout != nullptr) m_VertexLayout->Release();
    if (m_VertexShader != nullptr) { m_VertexShader->Release(); }
    if (m_PixelShader != nullptr) m_PixelShader->Release();
}

void Shader::SetVertexShader(ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ID3D11DeviceContext* context)
{
    context->VSSetShader(vertexShader, nullptr, 0);
    context->VSSetConstantBuffers(0, 1, &constantBuffer);
}

void Shader::SetVertexShader(ID3D11VertexShader* vertexShader, ID3D11DeviceContext* context)
{
    context->VSSetShader(vertexShader, nullptr, 0);
}

void Shader::SetPixelShader(ID3D11PixelShader* pixelShader, ID3D11Buffer* constantBuffer, ID3D11DeviceContext* context)
{
    context->PSSetShader(pixelShader, nullptr, 0);
    context->PSSetConstantBuffers(2, 1, &constantBuffer);
}

void Shader::SetPixelShader(ID3D11PixelShader* pixelShader, ID3D11DeviceContext* context)
{
    context->PSSetShader(pixelShader, nullptr, 0);
}

void Shader::SetInputLayout(ID3D11InputLayout* inputLayout, ID3D11DeviceContext* context)
{
    context->IASetInputLayout(inputLayout);
}
