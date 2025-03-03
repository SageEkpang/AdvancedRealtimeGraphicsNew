#include "Mesh.h"



Mesh::Mesh(Tag tag, ID3D11Buffer** vertexBuffer, ID3D11Buffer** indexBuffer, UINT indexSize, ID3D11DeviceContext* context, ID3D11Device* device)
	: Component(tag, device)
{
	m_VertexBuffer = *vertexBuffer;
	m_IndexBuffer = *indexBuffer;
	m_NumberOfVertices = indexSize;

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Mesh::Mesh(Tag tag, WORD* indices, SimpleVertex* vertices, UINT size, ID3D11DeviceContext* context, ID3D11Device* device) : Component(tag, device)
{
	m_NumberOfVertices = size;
	
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * m_NumberOfVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT t_HR = S_OK;
	D3D11_SUBRESOURCE_DATA InitData = {};

	// Creating Vertex Buffer
	try
	{
		InitData.pSysMem = vertices;
		HRESULT t_HR = device->CreateBuffer(&bd, &InitData, &m_VertexBuffer);

		if (FAILED(t_HR)) throw 0;
	}
	catch (...)
	{
	std:runtime_error(ERROR_VERTEX_BUFFER);
	}

	// Creating Index Buffer
	try
	{
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * m_NumberOfVertices;        // 36 vertices needed for 12 triangles in a triangle list
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		t_HR = device->CreateBuffer(&bd, &InitData, &m_IndexBuffer);

		if (FAILED(t_HR)) throw 0;
	}
	catch (...)
	{
		std::runtime_error(ERROR_INDEX_BUFFER);
	}

	// Set Primitive Type
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Mesh::~Mesh()
{
	if (m_VertexBuffer) m_VertexBuffer->Release();
	m_VertexBuffer = nullptr;

	if (m_IndexBuffer) m_IndexBuffer->Release();
	m_IndexBuffer = nullptr;
}

void Mesh::Update(const float deltaTime)
{

}

void Mesh::Draw(ID3D11DeviceContext* context)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->DrawIndexed(m_NumberOfVertices, 0, 0);

	// ComputeTangentFrame()

	//context->IASetVertexBuffers(0, 1, &m_MeshData->VertexBuffer, &m_MeshData->VBStride, &m_MeshData->VBOffset);
	//context->IASetIndexBuffer(m_MeshData->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	//context->DrawIndexed(m_MeshData->IndexCount, 0, 0);
}

void Mesh::CalculateTangentBinormal(SimpleVertex v0, SimpleVertex v1, SimpleVertex v2, XMFLOAT3& normal, XMFLOAT3& tangent, XMFLOAT3& binormal)
{
	XMVECTOR vv0 = XMLoadFloat3(&v0.Pos);
	XMVECTOR vv1 = XMLoadFloat3(&v1.Pos);
	XMVECTOR vv2 = XMLoadFloat3(&v2.Pos);

	XMVECTOR e0 = vv1 - vv0;
	XMVECTOR e1 = vv2 - vv0;

	XMVECTOR e01cross = XMVector3Cross(e0, e1);
	XMFLOAT3 normalOut;
	XMStoreFloat3(&normalOut, e01cross);
	normal = normalOut;

	//let P = v1 - v0
	XMVECTOR P = vv1 - vv0;
	//let Q = v2 - v0
	XMVECTOR Q = vv2 - vv0;
	float s1 = v1.TexCoord.x - v0.TexCoord.x;
	float t1 = v1.TexCoord.y - v0.TexCoord.y;
	float s2 = v2.TexCoord.x - v0.TexCoord.x;
	float t2 = v2.TexCoord.y - v0.TexCoord.y;

	float tmp = 0.0f;
	if (fabsf(s1 * t2 - s2 * t1) <= 0.0001f)
	{
		tmp = 1.0f;
	}
	else
	{
		tmp = 1.0f / (s1 * t2 - s2 * t1);
	}

	XMFLOAT3 PF3, QF3;
	XMStoreFloat3(&PF3, P);
	XMStoreFloat3(&QF3, Q);

	tangent.x = (t2 * PF3.x - t1 * QF3.x);
	tangent.y = (t2 * PF3.y - t1 * QF3.y);
	tangent.z = (t2 * PF3.z - t1 * QF3.z);

	tangent.x = tangent.x * tmp;
	tangent.y = tangent.y * tmp;
	tangent.z = tangent.z * tmp;

	XMVECTOR vn = XMLoadFloat3(&normal);
	XMVECTOR vt = XMLoadFloat3(&tangent);
	XMVECTOR vb = XMVector3Cross(vt, vn);

	vn = XMVector3Normalize(vn);
	vt = XMVector3Normalize(vt);
	vb = XMVector3Normalize(vb);

	XMStoreFloat3(&normal, vn);
	XMStoreFloat3(&tangent, vt);
	XMStoreFloat3(&binormal, vb);

	return;
}

// IMPORTANT NOTE!!
// NOTE!! - this assumes each face is using its own vertices (no shared vertices)
// so the index file would look like 0,1,2,3,4 and so on
// it won't work with shared vertices as the tangent / binormal for a vertex is related to a specific face
// REFERENCE this has largely been modified from "Mathematics for 3D Game Programmming and Computer Graphics" by Eric Lengyel
void Mesh::CalculateModelVectors(SimpleVertex* vertices, int vertexCount)
{
	int faceCount, i, index;
	SimpleVertex vertex1, vertex2, vertex3;
	XMFLOAT3 tangent, binormal, normal;


	// Calculate the number of faces in the model.
	faceCount = vertexCount / 3;

	// Initialize the index to the model data.
	index = 0;

	// Go through all the faces and calculate the the tangent, binormal, and normal vectors.
	for (i = 0; i < faceCount; i++)
	{
		// Get the three vertices for this face from the model.
		vertex1.Pos.x = vertices[index].Pos.x;
		vertex1.Pos.y = vertices[index].Pos.y;
		vertex1.Pos.z = vertices[index].Pos.z;
		vertex1.TexCoord.x = vertices[index].TexCoord.x;
		vertex1.TexCoord.y = vertices[index].TexCoord.y;
		vertex1.Normal.x = vertices[index].Normal.x;
		vertex1.Normal.y = vertices[index].Normal.y;
		vertex1.Normal.z = vertices[index].Normal.z;
		index++;

		vertex2.Pos.x = vertices[index].Pos.x;
		vertex2.Pos.y = vertices[index].Pos.y;
		vertex2.Pos.z = vertices[index].Pos.z;
		vertex2.TexCoord.x = vertices[index].TexCoord.x;
		vertex2.TexCoord.y = vertices[index].TexCoord.y;
		vertex2.Normal.x = vertices[index].Normal.x;
		vertex2.Normal.y = vertices[index].Normal.y;
		vertex2.Normal.z = vertices[index].Normal.z;
		index++;

		vertex3.Pos.x = vertices[index].Pos.x;
		vertex3.Pos.y = vertices[index].Pos.y;
		vertex3.Pos.z = vertices[index].Pos.z;
		vertex3.TexCoord.x = vertices[index].TexCoord.x;
		vertex3.TexCoord.y = vertices[index].TexCoord.y;
		vertex3.Normal.x = vertices[index].Normal.x;
		vertex3.Normal.y = vertices[index].Normal.y;
		vertex3.Normal.z = vertices[index].Normal.z;
		index++;

		// Calculate the tangent and binormal of that face.
		CalculateTangentBinormal(vertex1, vertex2, vertex3, normal, tangent, binormal);

		// Store the normal, tangent, and binormal for this face back in the model structure.
		vertices[index - 1].Normal.x = normal.x;
		vertices[index - 1].Normal.y = normal.y;
		vertices[index - 1].Normal.z = normal.z;
		vertices[index - 1].tangent.x = tangent.x;
		vertices[index - 1].tangent.y = tangent.y;
		vertices[index - 1].tangent.z = tangent.z;
		vertices[index - 1].biTangent.x = binormal.x;
		vertices[index - 1].biTangent.y = binormal.y;
		vertices[index - 1].biTangent.z = binormal.z;

		vertices[index - 2].Normal.x = normal.x;
		vertices[index - 2].Normal.y = normal.y;
		vertices[index - 2].Normal.z = normal.z;
		vertices[index - 2].tangent.x = tangent.x;
		vertices[index - 2].tangent.y = tangent.y;
		vertices[index - 2].tangent.z = tangent.z;
		vertices[index - 2].biTangent.x = binormal.x;
		vertices[index - 2].biTangent.y = binormal.y;
		vertices[index - 2].biTangent.z = binormal.z;

		vertices[index - 3].Normal.x = normal.x;
		vertices[index - 3].Normal.y = normal.y;
		vertices[index - 3].Normal.z = normal.z;
		vertices[index - 3].tangent.x = tangent.x;
		vertices[index - 3].tangent.y = tangent.y;
		vertices[index - 3].tangent.z = tangent.z;
		vertices[index - 3].biTangent.x = binormal.x;
		vertices[index - 3].biTangent.y = binormal.y;
		vertices[index - 3].biTangent.z = binormal.z;
	}
}
