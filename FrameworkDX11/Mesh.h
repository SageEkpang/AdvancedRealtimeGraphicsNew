#pragma once
#ifndef MESH_H
#define MESH_H

#include "Component.h"
#include "structures.h"
#include "ObjLoader.h"
#include "DirectXMesh.h"

class Mesh : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	UINT m_NumberOfVertices;

	MeshData* m_MeshData = nullptr;

public:

	// CLASS FUNCTION(s)
	Mesh(Tag tag, ID3D11Buffer** vertexBuffer, ID3D11Buffer** indexBuffer, UINT indexSize, ID3D11DeviceContext* context, ID3D11Device* device);
	Mesh(Tag tag, WORD* indices, SimpleVertex* vertices, UINT size, ID3D11DeviceContext* context, ID3D11Device* device);
	
	~Mesh();

	static void CalculateModelVectors(SimpleVertex* vertices, int vertexCount);
	static void CalculateTangentBinormal(SimpleVertex v0, SimpleVertex v1, SimpleVertex v2, XMFLOAT3& normal, XMFLOAT3& tangent, XMFLOAT3& binormal);

	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw(ID3D11DeviceContext* context) override;


	// GETTER FUNCTION(s)
	inline ID3D11Buffer* GetVertexBuffer() { return m_VertexBuffer; }
	inline ID3D11Buffer* GetIndexBuffer() { return m_IndexBuffer; }
};

#endif