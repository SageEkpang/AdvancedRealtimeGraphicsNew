#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform : public Component
{
private:

	// TRS
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	XMFLOAT4X4* m_World;
	XMFLOAT4X4* m_Parent;

	float m_PositionArray[3];
	float m_RotationArray[3];
	float m_ScaleArray[3];

public:

	// CLASS FUNCTION(s)
	Transform(Tag tag, ID3D11Device* device);
	~Transform();

	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw(ID3D11DeviceContext* context) override;


	// GETTER FUNCTION(s)
	XMMATRIX GetWorld() const { return XMLoadFloat4x4(m_World); }
	inline XMFLOAT4X4* GetParent() const { return m_Parent; }

	XMFLOAT3 GetPosition() const { return XMFLOAT3(m_PositionArray[0], m_PositionArray[1], m_PositionArray[2]); }
	float* GetPosition() { return m_PositionArray; }

	XMFLOAT3 GetRotation() const { return XMFLOAT3(m_RotationArray[0], m_RotationArray[1], m_RotationArray[2]); }
	float* GetRotation() { return m_RotationArray; }

	XMFLOAT3 GetScale() const { return XMFLOAT3(m_ScaleArray[0], m_ScaleArray[1], m_ScaleArray[2]); }
	float* GetScale() { return m_ScaleArray; }


	// SETTER FUNCTION(s)
	inline void SetPosition(XMFLOAT3 position) { m_PositionArray[0] = position.x, m_PositionArray[1] = position.y, m_PositionArray[2] = position.z; }
	inline void SetPosition(float x, float y, float z) { m_PositionArray[0] = x, m_PositionArray[1] = y, m_PositionArray[2] = z; }

	inline void SetRotation(XMFLOAT3 rotation) { m_RotationArray[0] = rotation.x, m_RotationArray[1] = rotation.y, m_RotationArray[2] = rotation.z; }
	inline void SetRotation(float pitch, float yaw, float roll) { m_RotationArray[0] = pitch, m_RotationArray[1] = yaw, m_RotationArray[2] = roll; }

	inline void SetScale(XMFLOAT3 scale) { m_ScaleArray[0] = scale.x, m_ScaleArray[1] = scale.y, m_ScaleArray[2] = scale.z; }
	inline void SetScale(float width, float height, float length) { m_ScaleArray[0] = width, m_ScaleArray[1] = height, m_ScaleArray[2] = length; }

	inline void SetParent(XMFLOAT4X4* parent) { m_Parent = parent; }

	// HELPER
	inline void MoveX(float direction) { m_Position.x += direction; }
	inline void MoveY(float direction) { m_Position.y += direction; }
	inline void MoveZ(float direction) { m_Position.z += direction; }
};

#endif