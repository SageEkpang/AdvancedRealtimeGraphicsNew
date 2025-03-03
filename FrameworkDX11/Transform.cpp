#include "Transform.h"

Transform::Transform(Tag tag, ID3D11Device* device) : Component(tag, device)
{
	m_World = new XMFLOAT4X4();
	m_Position = XMFLOAT3();
	m_Rotation = XMFLOAT3();
	m_Scale = XMFLOAT3();

	m_Parent = nullptr;

	m_PositionArray[0] = m_Position.x;
	m_PositionArray[1] = m_Position.y;
	m_PositionArray[2] = m_Position.z;

	m_RotationArray[0] = m_Rotation.x;
	m_RotationArray[1] = m_Rotation.y;
	m_RotationArray[2] = m_Rotation.z;

	m_ScaleArray[0] = m_Scale.x;
	m_ScaleArray[1] = m_Scale.y;
	m_ScaleArray[2] = m_Scale.z;

	XMStoreFloat4x4(m_World, XMMatrixIdentity());
}

Transform::~Transform()
{
	delete m_World;
	m_World = nullptr;
}

void Transform::Update(const float deltaTime)
{
	XMMATRIX t_TransalationMat = XMMatrixTranslation(m_PositionArray[0], m_PositionArray[1], m_PositionArray[2]);
	XMMATRIX t_RotationMat = XMMatrixRotationRollPitchYaw(m_RotationArray[0], m_RotationArray[1], m_RotationArray[2]);
	XMMATRIX t_ScaleMat = XMMatrixScaling(m_ScaleArray[0], m_ScaleArray[1], m_ScaleArray[2]);

	XMMATRIX t_World = t_ScaleMat * t_RotationMat * t_TransalationMat;

	XMStoreFloat4x4(m_World, t_World);

	// Parent Transformation
	if (m_Parent != nullptr) { XMStoreFloat4x4(m_World, XMLoadFloat4x4(m_World) * XMLoadFloat4x4(m_Parent)); }
}

void Transform::Draw(ID3D11DeviceContext* context)
{
	
}
