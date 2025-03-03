#include "ShaderEffect.h"

ShaderEffect::ShaderEffect(UINT width, UINT height, ID3D11Device* device)
{
    // DEPTH STENCIL TEXTURE DESCRIPTION
    m_Texture2DDepthDescription = { };
    m_Texture2DDepthDescription.Width = width;
    m_Texture2DDepthDescription.Height = height;
    m_Texture2DDepthDescription.MipLevels = 1;
    m_Texture2DDepthDescription.ArraySize = 1;
    m_Texture2DDepthDescription.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    m_Texture2DDepthDescription.SampleDesc.Count = 1;
    m_Texture2DDepthDescription.SampleDesc.Quality = 0;
    m_Texture2DDepthDescription.Usage = D3D11_USAGE_DEFAULT;
    m_Texture2DDepthDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    m_Texture2DDepthDescription.CPUAccessFlags = 0;
    m_Texture2DDepthDescription.MiscFlags = 0;


    // DEPTH STENCIL VIEW DESCRIPTION
    m_DepthStencilViewDescription = { };
    m_DepthStencilViewDescription.Format = m_Texture2DDepthDescription.Format;
    m_DepthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    m_DepthStencilViewDescription.Texture2D.MipSlice = 0;


    // RENDER TARGET TEXTURE DESCRIPTION
    m_Texture2DRenderTargetDescription = { };
    m_Texture2DRenderTargetDescription.Width = width;
    m_Texture2DRenderTargetDescription.Height = height;
    m_Texture2DRenderTargetDescription.MipLevels = 1;
    m_Texture2DRenderTargetDescription.ArraySize = 1;
    // m_Texture2DRenderTargetDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_Texture2DRenderTargetDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    m_Texture2DRenderTargetDescription.SampleDesc.Count = 1;
    // TextureDesc.SampleDesc.Quality = 0;
    m_Texture2DRenderTargetDescription.Usage = D3D11_USAGE_DEFAULT;
    m_Texture2DRenderTargetDescription.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    m_Texture2DRenderTargetDescription.CPUAccessFlags = 0;
    m_Texture2DRenderTargetDescription.MiscFlags = 0;


    // RENDER TARGET VIEW DESCRIPTION
    m_RenderTargetViewDescription = { };
    m_RenderTargetViewDescription.Format = m_Texture2DRenderTargetDescription.Format;
    m_RenderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    m_RenderTargetViewDescription.Texture2D.MipSlice = 0;


    // SAMPLE DESCRIPTION
    ZeroMemory(&m_SamplerDescription, sizeof(m_SamplerDescription));
    m_SamplerDescription.Filter = D3D11_FILTER_ANISOTROPIC;
    m_SamplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
    m_SamplerDescription.MinLOD = 0;
    m_SamplerDescription.MaxLOD = D3D11_FLOAT32_MAX;


    // SHADER RESOURCE VIEW DESCRIPTION
    m_ShaderResourceViewDescription = { };
    m_ShaderResourceViewDescription.Format = m_Texture2DRenderTargetDescription.Format;
    m_ShaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    m_ShaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
    m_ShaderResourceViewDescription.Texture2D.MipLevels = 1;


    // BLEND STATE DESCRIPTION
    m_BlendDescription = { };
    ZeroMemory(&m_BlendDescription, sizeof(m_BlendDescription));
    m_BlendDescription.RenderTarget[0].BlendEnable = FALSE;
    m_BlendDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    // INIT FUNCTION(s) (PRIVATE)
    MakeRenderTargetTexture2D(width, height, device);
    MakeDepthTexture2D(width, height, device);
    MakeDepthStencilView(device);
    MakeBlendState(device);

    MakeRenderTargetView(device);
    MakeShaderResourceView(device);
    MakeSamplerState(device);

}

ShaderEffect::ShaderEffect(UINT width, UINT height, ID3D11Device* device, UINT arraySize)
{
    // DEPTH STENCIL TEXTURE DESCRIPTION
    m_Texture2DDepthDescription = { };
    m_Texture2DDepthDescription.Width = width;
    m_Texture2DDepthDescription.Height = height;
    m_Texture2DDepthDescription.MipLevels = 1;
    m_Texture2DDepthDescription.ArraySize = 1;
    m_Texture2DDepthDescription.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    m_Texture2DDepthDescription.SampleDesc.Count = 1;
    m_Texture2DDepthDescription.SampleDesc.Quality = 0;
    m_Texture2DDepthDescription.Usage = D3D11_USAGE_DEFAULT;
    m_Texture2DDepthDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    m_Texture2DDepthDescription.CPUAccessFlags = 0;
    m_Texture2DDepthDescription.MiscFlags = 0;


    // DEPTH STENCIL VIEW DESCRIPTION
    m_DepthStencilViewDescription = { };
    m_DepthStencilViewDescription.Format = m_Texture2DDepthDescription.Format;
    m_DepthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    m_DepthStencilViewDescription.Texture2D.MipSlice = 0;


    // RENDER TARGET TEXTURE DESCRIPTION
    m_Texture2DRenderTargetDescription = { };
    m_Texture2DRenderTargetDescription.Width = width;
    m_Texture2DRenderTargetDescription.Height = height;
    m_Texture2DRenderTargetDescription.MipLevels = 1;
    m_Texture2DRenderTargetDescription.ArraySize = 1;
    // m_Texture2DRenderTargetDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_Texture2DRenderTargetDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    m_Texture2DRenderTargetDescription.SampleDesc.Count = 1;
    // TextureDesc.SampleDesc.Quality = 0;
    m_Texture2DRenderTargetDescription.Usage = D3D11_USAGE_DEFAULT;
    m_Texture2DRenderTargetDescription.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    m_Texture2DRenderTargetDescription.CPUAccessFlags = 0;
    m_Texture2DRenderTargetDescription.MiscFlags = 0;


    // RENDER TARGET VIEW DESCRIPTION
    m_RenderTargetViewDescription = { };
    m_RenderTargetViewDescription.Format = m_Texture2DRenderTargetDescription.Format;
    m_RenderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    m_RenderTargetViewDescription.Texture2D.MipSlice = 0;


    // SAMPLE DESCRIPTION
    ZeroMemory(&m_SamplerDescription, sizeof(m_SamplerDescription));
    m_SamplerDescription.Filter = D3D11_FILTER_ANISOTROPIC;
    m_SamplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
    m_SamplerDescription.MinLOD = 0;
    m_SamplerDescription.MaxLOD = D3D11_FLOAT32_MAX;


    // SHADER RESOURCE VIEW DESCRIPTION
    m_ShaderResourceViewDescription = { };
    m_ShaderResourceViewDescription.Format = m_Texture2DRenderTargetDescription.Format;
    m_ShaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    m_ShaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
    m_ShaderResourceViewDescription.Texture2D.MipLevels = 1;


    // BLEND STATE DESCRIPTION
    m_BlendDescription = { };
    ZeroMemory(&m_BlendDescription, sizeof(m_BlendDescription));
    m_BlendDescription.RenderTarget[0].BlendEnable = FALSE;
    m_BlendDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


    // INIT FUNCTION(s) (PRIVATE)
    MakeRenderTargetTexture2D(width, height, device);
    MakeDepthTexture2D(width, height, device);
    MakeDepthStencilView(device);
    MakeBlendState(device);

    MakeRenderTargetViewArray(device, arraySize);
    MakeShaderResourceViewArray(device, arraySize);
    MakeSamplerStateArray(device, arraySize);
}

ShaderEffect::~ShaderEffect()
{
    if (m_ShaderResourceView) m_ShaderResourceView->Release();
    if (m_RenderTargetView) m_RenderTargetView->Release();
    if (m_SamplerState) m_SamplerState->Release();
    if (m_RenderTargetTexture) m_RenderTargetTexture->Release();
    if (m_BlendState) m_BlendState->Release();

    if (m_DepthTexture) m_DepthTexture->Release();
    if (m_DepthStencilView) m_DepthStencilView->Release();
}

// PUBLIC FUNCTION(s)
void ShaderEffect::StartEffect(XMVECTORF32 colour, ID3D11DeviceContext* context)
{
    context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
    context->ClearRenderTargetView(m_RenderTargetView, colour);
    context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    context->OMSetBlendState(m_BlendState, 0, 0xffffffff);
}

void ShaderEffect::StartEffectArray(XMVECTORF32 colour, ID3D11DeviceContext* context)
{
    context->OMSetRenderTargets(MAX_ARRAY_SIZE, &m_RenderTargetViews[0], m_DepthStencilView);
    context->ClearRenderTargetView(*m_RenderTargetViews, colour);
    context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    context->OMSetBlendState(m_BlendState, 0, 0xffffffff);
}

void ShaderEffect::EndEffect(ID3D11DeviceContext* context)
{
    context->OMSetRenderTargets(0, NULL, NULL);
}

// STATIC FUNCTION(s)

void ShaderEffect::S_StartEffect(ID3D11RenderTargetView** renderTargetView, ID3D11DepthStencilView* depthStencilView, ID3D11BlendState* blendState, XMVECTORF32 colour, ID3D11DeviceContext* context)
{
    context->OMSetRenderTargets(1, renderTargetView, depthStencilView);
    context->ClearRenderTargetView(*renderTargetView, colour);
    context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    context->OMSetBlendState(blendState, 0, 0xffffffff);
}

void ShaderEffect::S_EndEffect(ID3D11DeviceContext* context)
{
    context->OMSetRenderTargets(0, NULL, NULL);
}

void ShaderEffect::S_MakeRenderTargetTexture2D(ID3D11Texture2D* texture2D, DXGI_FORMAT format, D3D11_USAGE usage, UINT bindFlags, UINT width, UINT height, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;

    D3D11_TEXTURE2D_DESC t_Text2DDesc = { };
    t_Text2DDesc.Width = width;
    t_Text2DDesc.Height = height;
    t_Text2DDesc.MipLevels = 1;
    t_Text2DDesc.ArraySize = 1;
    t_Text2DDesc.Format = format;
    t_Text2DDesc.SampleDesc.Count = 1;
    // TextureDesc.SampleDesc.Quality = 0;
    t_Text2DDesc.Usage = usage;
    t_Text2DDesc.BindFlags = bindFlags;
    t_Text2DDesc.CPUAccessFlags = 0;
    t_Text2DDesc.MiscFlags = 0;

    device->CreateTexture2D(&t_Text2DDesc, nullptr, &texture2D);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Static Render Target Texture 2D", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::S_MakeDepthTexture2D(ID3D11Texture2D** texture2D, DXGI_FORMAT format, D3D11_USAGE usage, UINT bindFlags, UINT width, UINT height, UINT count, UINT quality, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;

    D3D11_TEXTURE2D_DESC t_Text2DDesc = { };
    t_Text2DDesc.Width = width;
    t_Text2DDesc.Height = height;
    t_Text2DDesc.MipLevels = 1;
    t_Text2DDesc.ArraySize = 1;
    t_Text2DDesc.Format = format;
    t_Text2DDesc.SampleDesc.Count = count; // Count
    t_Text2DDesc.SampleDesc.Quality = quality; // Quality
    t_Text2DDesc.Usage = usage;
    t_Text2DDesc.BindFlags = bindFlags;
    t_Text2DDesc.CPUAccessFlags = 0;
    t_Text2DDesc.MiscFlags = 0;

    t_HR = device->CreateTexture2D(&t_Text2DDesc, nullptr, texture2D);

    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Static Depth Texture 2D", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::S_MakeDepthStencilView(ID3D11DepthStencilView** depthStencilView, ID3D11Texture2D* texture2D, DXGI_FORMAT format, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;

    D3D11_DEPTH_STENCIL_VIEW_DESC t_DepthStencilViewDesc = { };
    t_DepthStencilViewDesc.Format = format;
    t_DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    t_DepthStencilViewDesc.Texture2D.MipSlice = 0;

    t_HR = device->CreateDepthStencilView(texture2D, &t_DepthStencilViewDesc, depthStencilView);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Static Depth Stencil View.", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::S_MakeBlendState(ID3D11BlendState* blendState, UINT8 renderTargetWriteMask, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;

    D3D11_BLEND_DESC t_BlendDesc = { };
    ZeroMemory(&t_BlendDesc, sizeof(t_BlendDesc));
    t_BlendDesc.RenderTarget[0].BlendEnable = FALSE;
    t_BlendDesc.RenderTarget[0].RenderTargetWriteMask = renderTargetWriteMask;

    t_HR = device->CreateBlendState(&t_BlendDesc, &blendState);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Static Blend State", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::S_MakeRenderTargetView(ID3D11RenderTargetView** renderTargetView, ID3D11Texture2D* texture2D, DXGI_FORMAT format, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    D3D11_RENDER_TARGET_VIEW_DESC t_RenderTargetViewDesc = { };
    t_RenderTargetViewDesc.Format = format;
    t_RenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    t_RenderTargetViewDesc.Texture2D.MipSlice = 0;

    t_HR = device->CreateRenderTargetView(texture2D, &t_RenderTargetViewDesc, renderTargetView);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Static Render Target View", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::S_MakeRenderTargetViewAlt(ID3D11RenderTargetView** renderTargetView, ID3D11Texture2D* texture2D, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    t_HR = device->CreateRenderTargetView(texture2D, nullptr, renderTargetView);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Static Render Target View Alt", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::S_MakeShaderResourceView(ID3D11ShaderResourceView* shaderResourceView, ID3D11Texture2D* texture2D, DXGI_FORMAT format, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;

    D3D11_SHADER_RESOURCE_VIEW_DESC t_ShaderResourceViewDesc;
    t_ShaderResourceViewDesc.Format = format;
    t_ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    t_ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    t_ShaderResourceViewDesc.Texture2D.MipLevels = 1;

    t_HR = device->CreateShaderResourceView(texture2D, &t_ShaderResourceViewDesc, &shaderResourceView);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create a Static Shader Resource View.", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::S_MakeSamplerState(ID3D11SamplerState* samplerState, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    D3D11_SAMPLER_DESC t_SamplerDesc;
    ZeroMemory(&t_SamplerDesc, sizeof(t_SamplerDesc));
    t_SamplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    t_SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    t_SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    t_SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    t_SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    t_SamplerDesc.MinLOD = 0;
    t_SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    t_HR = device->CreateSamplerState(&t_SamplerDesc, &samplerState);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Static Sampler State", L"Error", MB_OK);
        return;
    }
}



// PRIVATE FUNCTION(s)
void ShaderEffect::MakeRenderTargetTexture2D(UINT width, UINT height, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    device->CreateTexture2D(&m_Texture2DRenderTargetDescription, nullptr, &m_RenderTargetTexture);
    if (FAILED(t_HR))
    { 
        MessageBox(nullptr, L"Failed to Create Render Target Texture 2D", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::MakeDepthTexture2D(UINT width, UINT height, ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    t_HR = device->CreateTexture2D(&m_Texture2DDepthDescription, nullptr, &m_DepthTexture);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Depth Texture 2D", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::MakeDepthStencilView(ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    t_HR = device->CreateDepthStencilView(m_DepthTexture, &m_DepthStencilViewDescription, &m_DepthStencilView);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Depth Stencil View.", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::MakeBlendState(ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    t_HR = device->CreateBlendState(&m_BlendDescription, &m_BlendState);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Blend State", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::MakeRenderTargetView(ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    t_HR = device->CreateRenderTargetView(m_RenderTargetTexture, &m_RenderTargetViewDescription, &m_RenderTargetView);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Render Target View", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::MakeShaderResourceView(ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    t_HR = device->CreateShaderResourceView(m_RenderTargetTexture, &m_ShaderResourceViewDescription, &m_ShaderResourceView);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create a Shader Resource View.", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::MakeSamplerState(ID3D11Device* device)
{
    HRESULT t_HR = S_OK;
    device->CreateSamplerState(&m_SamplerDescription, &m_SamplerState);
    if (FAILED(t_HR))
    {
        MessageBox(nullptr, L"Failed to Create Sampler State", L"Error", MB_OK);
        return;
    }
}

void ShaderEffect::MakeRenderTargetViewArray(ID3D11Device* device, UINT arraySize)
{
    for (UINT i = 0; i < arraySize; ++i)
    {
        HRESULT t_HR = S_OK;
        t_HR = device->CreateRenderTargetView(m_RenderTargetTexture, &m_RenderTargetViewDescription, &m_RenderTargetViews[i]);
        if (FAILED(t_HR))
        {
            MessageBox(nullptr, L"Failed to Create Render Target View", L"Error", MB_OK);
            return;
        }
    }
}

void ShaderEffect::MakeShaderResourceViewArray(ID3D11Device* device, UINT arraySize)
{
    for (UINT i = 0; i < arraySize; ++i)
    {
        HRESULT t_HR = S_OK;
        t_HR = device->CreateShaderResourceView(m_RenderTargetTexture, &m_ShaderResourceViewDescription, &m_ShaderResourceViews[i]);
        if (FAILED(t_HR))
        {
            MessageBox(nullptr, L"Failed to Create a Shader Resource View.", L"Error", MB_OK);
            return;
        }
    }
}

void ShaderEffect::MakeSamplerStateArray(ID3D11Device* device, UINT arraySize)
{
    for (UINT i = 0; i < arraySize; ++i)
    {
        HRESULT t_HR = S_OK;
        device->CreateSamplerState(&m_SamplerDescription, &m_SamplerStates[i]);
        if (FAILED(t_HR))
        {
            MessageBox(nullptr, L"Failed to Create Sampler State", L"Error", MB_OK);
            return;
        }
    }
}

