  #pragma once
#ifndef SHADER_EFFECTS_MANAGER_H
#define SHADER_EFFECTS_MANAGER_H

// NEEDED INCLUDE(s)
#include "constants.h"
#include "structures.h"

// CLASS INCLUDE(s)
#include "Mesh.h"
#include "ShaderEffect.h"
#include "Shader.h"

// TODO: Add a constant buffer value to the shader storage so shaders can be changed dynamically
struct ShaderStorage
{
	const wchar_t* name;
	Shader* shader;
	bool isActive;

	ShaderStorage(const wchar_t* name, Shader* shader, bool isActive)
	{
		this->name = name;
		this->shader = shader;
		this->isActive = isActive;
	}

	ShaderStorage(const ShaderStorage& value)
	{
		this->name = value.name;
		this->shader = value.shader;
		this->isActive = value.isActive;
	}
};

// NOTE: This will be for the Post Process Effects
class ShaderEffectsManager
{
private:

	// SHADER VECTORS
	std::vector<const wchar_t*> m_ShaderNames;
	std::vector<ShaderEffect*> m_ShaderEffectsVec;
	std::vector<ShaderStorage> m_ShaderStorageArray;
	std::vector<UINT> m_ShaderIndexs;

public:

	// CLASS FUNCTION(s)
	ShaderEffectsManager(ID3D11DeviceContext* context, ID3D11Device* device);
	~ShaderEffectsManager();


	// BASE FUNCTION(s)
	void Draw(UINT width, UINT height, ID3D11DeviceContext* context, ID3D11Device* device, Mesh* quadMesh);
	void ClearShaderManager();


	// GETTER FUNCTION(s)
	inline std::vector<ShaderStorage>& GetShaderStorageArray() { return m_ShaderStorageArray; }

};

#endif