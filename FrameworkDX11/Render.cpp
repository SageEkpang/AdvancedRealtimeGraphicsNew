#include "Render.h"

Render::Render(Tag tag, ID3D11Device* device) : Component(tag, device)
{
	// Textures
	m_BaseTexture = nullptr;
	m_NormalTexture = nullptr;
	m_SpecularTexture = nullptr;
	m_RoughnessTexture = nullptr;

	// Sample States
	m_BaseSampleState = nullptr;
	m_NormalSampleState = nullptr;
	m_SpecularSamplerState = nullptr;
	m_RoughnessSamplerState = nullptr;

	HRESULT t_HR = S_OK;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Creating the Sample States
	try
	{
		t_HR = device->CreateSamplerState(&sampDesc, &m_BaseSampleState);
		t_HR = device->CreateSamplerState(&sampDesc, &m_NormalSampleState);
		t_HR = device->CreateSamplerState(&sampDesc, &m_SpecularSamplerState);
		t_HR = device->CreateSamplerState(&sampDesc, &m_RoughnessSamplerState);

		if (FAILED(t_HR)) throw 0;
	}
	catch(...)
	{
		std::runtime_error("Sample States not Set");
	}

	m_Material.Material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Material.Material.Specular = XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f);
	m_Material.Material.SpecularPower = 32.0f;
	m_Material.Material.UseTexture = false;

	// Creating Material Constant Buffer
	try
	{
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(MaterialPropertiesConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		t_HR = device->CreateBuffer(&bd, nullptr, &m_MaterialConstantBuffer);

		if (FAILED(t_HR)) throw 0;
	}
	catch (...)
	{
		std::runtime_error("Material Constant Buffer not Set");
	}
}

Render::~Render()
{
	// CLEAN UP VARIABLE(s)

	// Textures
	if (m_BaseTexture) m_BaseTexture->Release();
	if (m_NormalTexture) m_NormalTexture->Release();
	if (m_SpecularTexture) m_SpecularTexture->Release();
	if (m_RoughnessTexture) m_RoughnessTexture->Release();

	// Sample State
	if (m_BaseSampleState) m_BaseSampleState->Release();
	if (m_NormalSampleState) m_NormalSampleState->Release();
	if (m_SpecularSamplerState) m_SpecularSamplerState->Release();
	if (m_RoughnessSamplerState) m_RoughnessSamplerState->Release();

	// Material
	if (m_MaterialConstantBuffer) m_MaterialConstantBuffer->Release();
}

void Render::Update(const float deltaTime)
{

}

void Render::Draw(ID3D11DeviceContext* context)
{
	// BASE TEXTURE
	// TODO: CHECK IF NULL
	// NOTE: Setting Shader Resource in main, this bit of copde will overwrite it
	context->PSSetShaderResources(0, 1, &m_BaseTexture);
	context->PSSetSamplers(0, 1, &m_BaseSampleState);

	// NORMAL TEXTURE
	context->PSSetShaderResources(1, 1, &m_NormalTexture);
	context->PSSetSamplers(1, 1, &m_NormalSampleState);

	// SPECULAR TEXTURE
	context->PSSetShaderResources(2, 1, &m_SpecularTexture);
	context->PSSetSamplers(2, 1, &m_SpecularSamplerState);

	// ROUGHNESS TEXTURE
	context->PSSetShaderResources(3, 1, &m_RoughnessTexture);
	context->PSSetSamplers(3, 1, &m_RoughnessSamplerState);

	// UPDATE MATERIAL RESOURCE
	context->UpdateSubresource(m_MaterialConstantBuffer, 0, nullptr, &m_Material, 0, 0);
}

void Render::SetBaseTexture(const wchar_t* filePath, ID3D11Device* device)
{
	HRESULT t_HR = S_OK;
	t_HR = CreateDDSTextureFromFile(device, filePath, nullptr, &m_BaseTexture);
	if (FAILED(t_HR))
	{
		std::cerr << "Base Texture Could not be Loaded, check file path" << std::endl;
		return;
	}

	// NOTE: Assumes texture has been set
	m_Material.Material.UseTexture = true;
	m_HasBase = 1;
}

void Render::SetShaderBaseTexture(ID3D11ShaderResourceView** shaderResource)
{
	m_BaseTexture = *shaderResource;
}

void Render::SetNormalTexture(const wchar_t* filePath, ID3D11Device* device)
{
	HRESULT t_HR = S_OK;
	t_HR = CreateDDSTextureFromFile(device, filePath, nullptr, &m_NormalTexture);
	if (FAILED(t_HR))
	{
		std::cerr << "Normal Texture Could not be Loaded, check file path" << std::endl;
		return;
	}

	m_HasNormal = 1;
}

void Render::SetShaderNormalTexture(ID3D11ShaderResourceView** shaderResource)
{
	m_NormalTexture = *shaderResource;
}

void Render::SetSpecularTexture(const wchar_t* filePath, ID3D11Device* device)
{
	HRESULT t_HR = S_OK;
	t_HR = CreateDDSTextureFromFile(device, filePath, nullptr, &m_SpecularTexture);
	if (FAILED(t_HR))
	{
		std::cerr << "Specular Texture Could not be Loaded, check file path" << std::endl;
		return;
	}

	m_HasSpecular = 1;
}

void Render::SetShaderSpecularTexture(ID3D11ShaderResourceView** shaderResource)
{
	m_SpecularTexture = *shaderResource;
}

void Render::SetRoughnessTexture(const wchar_t* filePath, ID3D11Device* device)
{
	HRESULT t_HR = S_OK;
	t_HR = CreateDDSTextureFromFile(device, filePath, nullptr, &m_RoughnessTexture);
	if (FAILED(t_HR))
	{
		std::cerr << "Roughness Texture Could not be Loaded, check file path" << std::endl;
		return;
	}
}

void Render::SetShaderPositionTexture(ID3D11ShaderResourceView** shaderResource)
{
	m_RoughnessTexture = *shaderResource;
}

void Render::SetTexture(const wchar_t* filePath, ID3D11ShaderResourceView* texture, MaterialPropertiesConstantBuffer materialBuffer, ID3D11Buffer* material, ID3D11SamplerState* sampler, ID3D11Device* device)
{
	HRESULT t_HR = S_OK;
	t_HR = CreateDDSTextureFromFile(device, filePath, nullptr, &texture);
	if (FAILED(t_HR))
	{
		std::cerr << "Base Texture Could not be Loaded, check file path" << std::endl;
		return;
	}

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	t_HR = device->CreateSamplerState(&sampDesc, &sampler);
	if (FAILED(t_HR))
	{
		std::cerr << "Base Texture Could not be Loaded, check file path" << std::endl;
		return;
	}
}

