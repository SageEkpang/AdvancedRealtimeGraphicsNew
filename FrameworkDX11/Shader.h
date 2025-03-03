#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "structures.h"
#include "constants.h"

class Shader
{
private: // PRIVATE VARIABLE(s)

	ID3D11InputLayout* m_VertexLayout = nullptr;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;

private: // PRIVATE FUNCTION(s)

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Shader(const WCHAR* shaderFile, D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize, ID3D11DeviceContext* context, ID3D11Device* device);
	~Shader();


	// BASE FUNCTION(s)


	// GETTER FUNCTION(s)
	inline ID3D11VertexShader* GetVertexShader() { return m_VertexShader; }
	inline ID3D11PixelShader* GetPixelShader() { return m_PixelShader; }
	inline ID3D11InputLayout* GetInputLayout() { return m_VertexLayout; }

	// SETTER FUNCTION(s)
	static void SetVertexShader(ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ID3D11DeviceContext* context);
	static void SetVertexShader(ID3D11VertexShader* vertexShader, ID3D11DeviceContext* context);
	static void SetPixelShader(ID3D11PixelShader* pixelShader, ID3D11Buffer* constantBuffer, ID3D11DeviceContext* context);
	static void SetPixelShader(ID3D11PixelShader* pixelShader, ID3D11DeviceContext* context);

	static void SetInputLayout(ID3D11InputLayout* inputLayout, ID3D11DeviceContext* context);

};

#endif