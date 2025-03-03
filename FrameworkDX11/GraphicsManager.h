#pragma once
#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

// NEEDED INCLUDE(s)
#include "constants.h"
#include "structures.h"

// CLASS INCLUDE(s)
#include "Camera.h"
#include "DrawableGameObject.h"
#include "ShaderEffectsManager.h"
#include "Shader.h"
#include "ShaderEffect.h"
#include "LightObject.h"
#include "Timer.h"

#include "MeshLoader.h"

class GraphicsManager
{
private: // PRIVATE FUNCTION(s)

	// INIT VARIABLE(s)
	#pragma region Default Parameters

	HINSTANCE m_HInst = nullptr;
	HWND m_HWnd = nullptr;
	D3D_DRIVER_TYPE m_DriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;


	ID3D11Device* m_d3dDevice = nullptr;
	ID3D11Device1* m_d3dDevice1 = nullptr;

	ID3D11DeviceContext* m_ImmediateContext = nullptr;
	ID3D11DeviceContext1* m_ImmediateContext1 = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;
	IDXGISwapChain1* m_SwapChain1 = nullptr;

	#pragma endregion

	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	ID3D11Texture2D* m_DepthStencil = nullptr;

	ID3D11Buffer* m_ConstantBuffer = nullptr;
	ID3D11Buffer* m_LightConstantBuffer = nullptr;

	ID3D11RasterizerState* m_DefaultRasterizer;
	ID3D11RasterizerState* m_WireframeRasterizer;
	ID3D11DepthStencilState* m_SkyBoxState;
	ID3D11BlendState* m_DefaultBlendState;

	Mesh* m_QuadMesh;

	Camera* m_Camera;
	Timer* m_Timer;

	// SIMULATION VARIABLE(s)
	LightPropertiesConstantBuffer m_LightProps;
	std::array<LightObject*, 3> m_Lights;

	// OBJECTS
	std::vector<DrawableGameObject*> m_Objects;

	// NOTE: This is for the Post-Processing Effects
	ShaderEffectsManager* m_ShaderEffectsManager;

	ShaderEffect* m_OutputEffect;

	// SHADER VARIABLE(s)
	ShaderEffect* m_BaseEffect;
	ShaderEffect* m_ColourEffect;
	ShaderEffect* m_BloomEffect;
	ShaderEffect* m_DepthOfFieldEffect;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;

	Shader* m_BaseShader = nullptr;
	Shader* m_ColourShader = nullptr;
	Shader* m_RenderTargetShader = nullptr;
	Shader* m_BloomShader = nullptr;
	Shader* m_DepthOfFieldShader = nullptr;
	Shader* m_QuadShader = nullptr;


	// GBUFFER SHADER VARIABLE(s)
	ShaderEffect* m_GbufferEffect;
	ShaderEffect* m_PositionEffect;
	ShaderEffect* m_SpecularEffect;
	ShaderEffect* m_DepthEffect;
	ShaderEffect* m_NewNormalEffect;

	Shader* m_GbufferShader = nullptr;
	Shader* m_PositionShader = nullptr;
	Shader* m_SpecularShader = nullptr;
	Shader* m_NewNormalShader = nullptr;
	Shader* m_DepthBufferShader = nullptr;

	bool m_RenderAlternative = true;
	bool m_RenderDepthOfField = false;

public: // PUBLIC VARIABLE(s)

	// STATIC INSTANCE

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	GraphicsManager(HINSTANCE hInstance, int nCmdShow, int windowWidth, int windowHeight);
	~GraphicsManager();

	// BASE FUNCTION(s)
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void Process();
	void Showcase();

	// INIT FUNCTION(s)
	HRESULT InitDevice();
	HRESULT InitGUI();
	HRESULT	InitRunTimeParameters();
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

	// GENERAL FUNCTION(s)
	static void CenterMouseInWindow(HWND hWnd);

	// HELPER FUNCTION(s)
	void BeginGUI();
	void ProcessGUI();
	void ShowcaseGUI(); // NOTE: This will be for the shader resource files
	void EndGUI();
};

#endif // !GRAPHICS_MANAGER_H
