#pragma once
#ifndef RENDER_H
#define RENDER_H

#include "Component.h"

class Render : public Component
{
private:

	ID3D11ShaderResourceView* m_BaseTexture;
	ID3D11ShaderResourceView* m_NormalTexture;
	ID3D11ShaderResourceView* m_SpecularTexture;
	ID3D11ShaderResourceView* m_RoughnessTexture;

	ID3D11SamplerState* m_BaseSampleState;
	ID3D11SamplerState* m_NormalSampleState;
	ID3D11SamplerState* m_SpecularSamplerState;
	ID3D11SamplerState* m_RoughnessSamplerState;

	MaterialPropertiesConstantBuffer m_Material;
	ID3D11Buffer* m_MaterialConstantBuffer = nullptr;

	int m_HasBase = 0;
	int m_HasNormal = 0;
	int m_HasSpecular = 0;

public:

	// CLASS FUNCTION(s)
	Render(Tag tag, ID3D11Device* device);
	~Render() override;
	
	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw(ID3D11DeviceContext* context) override;
	void DrawAlt(ID3D11DeviceContext* context);
	
	// GETTER FUNCTION(s)
	inline ID3D11ShaderResourceView** GetBaseTexture() { return &m_BaseTexture; }
	inline ID3D11ShaderResourceView** GetNormalTexture() { return &m_NormalTexture; }
	inline ID3D11ShaderResourceView** GetSpecularTexture() { return &m_SpecularTexture; }
	inline ID3D11ShaderResourceView** GetRoughnessTexture() { return &m_RoughnessTexture; }

	inline ID3D11SamplerState** GetBaseTextureState() { return &m_BaseSampleState; }
	inline ID3D11SamplerState** GetNormalTextureState() { return &m_NormalSampleState; }
	inline ID3D11SamplerState** GetSpecularTextureState() { return &m_SpecularSamplerState; }
	inline ID3D11SamplerState** GetRoughnessTextureState() { return &m_RoughnessSamplerState; }

	inline MaterialPropertiesConstantBuffer GetMaterial() const { return m_Material; }
	inline ID3D11Buffer* GetMaterialBuffer() { return m_MaterialConstantBuffer; }

	// Boolean Functions
	inline XMFLOAT4 GetHasNormal() { return XMFLOAT4(m_HasNormal, 0.0f, 0.0f, 1.0f); }
	inline XMFLOAT4 GetHasBase() { return XMFLOAT4(m_HasBase, 0.0f, 0.0f, 1.0f); }
	inline XMFLOAT4 GetHasSpecular() { return XMFLOAT4(m_HasSpecular, 0.0f, 0.0f, 1.0f); }


	// SETTER FUNCTION(s)
	void SetBaseTexture(const wchar_t* filePath, ID3D11Device* device);
	void SetShaderBaseTexture(ID3D11ShaderResourceView** shaderResource);

	void SetNormalTexture(const wchar_t* filePath, ID3D11Device* device);
	void SetShaderNormalTexture(ID3D11ShaderResourceView** shaderResource);

	void SetSpecularTexture(const wchar_t* filePath, ID3D11Device* device);
	void SetShaderSpecularTexture(ID3D11ShaderResourceView** shaderResource);

	void SetRoughnessTexture(const wchar_t* filePath, ID3D11Device* device);
	void SetShaderPositionTexture(ID3D11ShaderResourceView** shaderResource);

	static void SetTexture(const wchar_t* filePath, ID3D11ShaderResourceView* texture, MaterialPropertiesConstantBuffer materialBuffer, ID3D11Buffer* material, ID3D11SamplerState* sampler, ID3D11Device* device);

	// void SetBaseShaderResource(ID3D11ShaderResourceView** resource, ID3D11Device* device);
	// void SetNormalTextureResource(ID3D11ShaderResourceView* resource, ID3D11Device* device);


};

#endif