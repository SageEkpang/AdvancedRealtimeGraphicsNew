#pragma once
#ifndef SHADER_EFFECT_H
#define SHADER_EFFECT_H

#include "structures.h"
#include "constants.h"

#define MAX_ARRAY_SIZE 4

class ShaderEffect
{
private: // PRIVATE VARIABLE(s)

	// DESCRIPTION(s)
	D3D11_SHADER_RESOURCE_VIEW_DESC m_ShaderResourceViewDescription;
	D3D11_RENDER_TARGET_VIEW_DESC m_RenderTargetViewDescription;
	D3D11_DEPTH_STENCIL_VIEW_DESC m_DepthStencilViewDescription;
	D3D11_TEXTURE2D_DESC m_Texture2DDepthDescription;
	D3D11_TEXTURE2D_DESC m_Texture2DRenderTargetDescription;
	D3D11_SAMPLER_DESC m_SamplerDescription;
	D3D11_BLEND_DESC m_BlendDescription;

	// VARIABLE(s)
	ID3D11ShaderResourceView* m_ShaderResourceView = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11SamplerState* m_SamplerState = nullptr;
	ID3D11Texture2D* m_RenderTargetTexture = nullptr;
	ID3D11BlendState* m_BlendState = nullptr;

	// Window size diference (If the render to texture size differs from the main back buffer (window) size, you will need to create depth-stencil buffer resources too) 
	// Note the viewport and the projection matrix also make use of the back buffer width, so initially it might be wise to have the same render to texture size as the back buffer and experiment with changing these later
	ID3D11Texture2D* m_DepthTexture = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;

	// ARRAY VARIABLE(s)
	ID3D11RenderTargetView* m_RenderTargetViews[MAX_ARRAY_SIZE];
	ID3D11ShaderResourceView* m_ShaderResourceViews[MAX_ARRAY_SIZE];
	ID3D11SamplerState* m_SamplerStates[MAX_ARRAY_SIZE];

private: // PRIVATE FUNCTION(s)

	// HELPER FUNCTION(s)
	void MakeRenderTargetTexture2D(UINT width, UINT height, ID3D11Device* device);
	void MakeDepthTexture2D(UINT width, UINT height, ID3D11Device* device);
	void MakeDepthStencilView(ID3D11Device* device);
	void MakeBlendState(ID3D11Device* device);

	void MakeRenderTargetView(ID3D11Device* device);
	void MakeShaderResourceView(ID3D11Device* device);
	void MakeSamplerState(ID3D11Device* device);

	// HELPER ARRAY FUNCTION(s)
	void MakeRenderTargetViewArray(ID3D11Device* device, UINT arraySize);
	void MakeShaderResourceViewArray(ID3D11Device* device, UINT arraySize);
	void MakeSamplerStateArray(ID3D11Device* device, UINT arraySize);


public: // PUBLIC VARIABLE(s)

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	ShaderEffect(UINT width, UINT height, ID3D11Device* device);
	ShaderEffect(UINT width, UINT height, ID3D11Device* device, UINT arrsySize);

	/// <summary> Default Destructor for Class </summary>
	~ShaderEffect();


	// HELPER FUNCTION(s)

	void StartEffect(XMVECTORF32 colour, ID3D11DeviceContext* context);
	void StartEffectArray(XMVECTORF32 colour, ID3D11DeviceContext* context);
	void EndEffect(ID3D11DeviceContext* context);

	// STATIC FUNCTION(s)
	static void S_StartEffect(ID3D11RenderTargetView** renderTargetView, ID3D11DepthStencilView* depthStencilView, ID3D11BlendState* blendState, XMVECTORF32 colour, ID3D11DeviceContext* context);
	static void S_EndEffect(ID3D11DeviceContext* context);

	static void S_MakeRenderTargetTexture2D(ID3D11Texture2D* texture2D, DXGI_FORMAT format, D3D11_USAGE usage, UINT bindFlags, UINT width, UINT height, ID3D11Device* device);
	static void S_MakeDepthTexture2D(ID3D11Texture2D** texture2D, DXGI_FORMAT format, D3D11_USAGE usage, UINT bindFlags, UINT width, UINT height, UINT count, UINT quality, ID3D11Device* device);
	static void S_MakeDepthStencilView(ID3D11DepthStencilView** depthStencilView, ID3D11Texture2D* texture2D, DXGI_FORMAT format, ID3D11Device* device);
	static void S_MakeBlendState(ID3D11BlendState* blendState, UINT8 renderTargetWriteMask, ID3D11Device* device);
	static void S_MakeRenderTargetView(ID3D11RenderTargetView** renderTargetView, ID3D11Texture2D* texture2D, DXGI_FORMAT format, ID3D11Device* device);
	static void S_MakeRenderTargetViewAlt(ID3D11RenderTargetView** renderTargetView, ID3D11Texture2D* texture2D, ID3D11Device* device);
	static void S_MakeShaderResourceView(ID3D11ShaderResourceView* shaderResourceView, ID3D11Texture2D* texture2D, DXGI_FORMAT format, ID3D11Device* device);
	static void S_MakeSamplerState(ID3D11SamplerState* samplerState, ID3D11Device* device);

	// GETTER FUNCTION(s)
	inline ID3D11ShaderResourceView** GetShaderResourceView() { return &m_ShaderResourceView; }
	inline ID3D11RenderTargetView* GetRenderTargetView() { return m_RenderTargetView; }
	inline ID3D11SamplerState** GetSamplerState() { return &m_SamplerState; }
	inline ID3D11Texture2D* GetRenderTargetTexture() { return m_RenderTargetTexture; }
	inline ID3D11BlendState* GetBlendState() { return m_BlendState; }
	inline ID3D11Texture2D* GetDepthTexture() { return m_DepthTexture; }
	inline ID3D11DepthStencilView* GetDepthStencilView() { return m_DepthStencilView; }

};


#endif