#include "Billboard.h"

Billboard::Billboard(const wchar_t* filePath, ID3D11DeviceContext* context, ID3D11Device* device)
{
	m_TransformComponent = new Transform(Tag("Billboard Transform"), device);

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

	t_HR = device->CreateSamplerState(&sampDesc, &m_TextureSample);
	if (FAILED(t_HR)) { std::cerr << "Failed to Load Billboard Texture Sample" << std::endl; }

	t_HR = CreateDDSTextureFromFile(device, filePath, nullptr, &m_Texture);
	if (FAILED(t_HR)) { std::cerr << "Failed to Load Billboard Texture Data" << std::endl; }

	// SHADER INIT
	D3D11_INPUT_ELEMENT_DESC t_BillboardLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	m_BillboardShader = new Shader(L"BillboardShader", t_BillboardLayout, ARRAYSIZE(t_BillboardLayout), context, device);

}

Billboard::~Billboard()
{
	if (m_Texture) m_Texture->Release();
	if (m_TextureSample) m_TextureSample->Release();

	if (m_TransformComponent != nullptr) delete m_TransformComponent;
}

void Billboard::Update(Camera* camera, const float deltaTime)
{
	m_TransformComponent->Update(deltaTime);

	// XMMATRIX t_TempWorld = XMMatrixInverse(nullptr, camera->GetViewMatrix());
	// XMFLOAT3 t_CameraRightWorld = XMFLOAT3(camera->GetPureViewMatrix()._11, camera->GetPureViewMatrix()._21, camera->GetPureViewMatrix()._31);
	// XMFLOAT3 t_CameraUp = XMFLOAT3(camera->GetPureViewMatrix()._12, camera->GetPureViewMatrix()._22, camera->GetPureViewMatrix()._32);


	// XMStoreFloat4x4();
}

void Billboard::Draw(ID3D11DeviceContext* context, ID3D11Device* device)
{
	context->VSSetShader(m_BillboardShader->GetVertexShader(), nullptr, 0);
	context->PSSetShader(m_BillboardShader->GetPixelShader(), nullptr, 0);

	context->PSSetShaderResources(0, 1, &m_Texture);
	context->PSSetSamplers(0, 1, &m_TextureSample);
}
