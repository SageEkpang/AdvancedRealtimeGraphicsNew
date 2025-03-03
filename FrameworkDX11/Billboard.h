#pragma once
#ifndef BILLBOARD_H
#define BILLBOARD_H

// NEEDED INCLUDE(s)
#include "constants.h"
#include "structures.h"

#include "Transform.h"
#include "Shader.h"

#include "Camera.h"

class Billboard
{
private: // PRIVATE VARIABLE(s)

	Transform* m_TransformComponent;

	ID3D11SamplerState* m_TextureSample;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;

	// SHADER VARIABLE(s)
	Shader* m_BillboardShader;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Billboard(const wchar_t* filePath, ID3D11DeviceContext* context, ID3D11Device* device);
	~Billboard();


	// BASE FUNCTION(s)
	void Update(Camera* camera, const float deltaTime);
	void Draw(ID3D11DeviceContext* context, ID3D11Device* device);


	// GETTER FUNCTION(s)
	Transform* GetTransform() { return m_TransformComponent; }


	// SETTER FUNCTION(s)



};

#endif