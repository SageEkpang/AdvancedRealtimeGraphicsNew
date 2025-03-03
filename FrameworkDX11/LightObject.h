#pragma once
#ifndef LIGHT_OBJECT_H
#define LIGHT_OBJECT_H

// NEEDED INCLUDE(s)
#include "structures.h"
#include "constants.h"

// TODO: LATER ON, MOVE TO COMPONENT SYSTEM
// CLASS INCLUDE(s)
#include "Transform.h"
#include "Render.h"

#include "FloatMaths.h"

using namespace FloatMaths;

// FORWARD DEC(s)
class Camera;

class LightObject
{
private: // PRIVATE VARIABLE(s)

	Light m_Light;

	float m_Position[4];
	float m_Direction[4];
	float m_Colour[4];
	float m_Intensity = 1.f;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	LightObject(ID3D11Device* device);
	~LightObject();

	
	// BASE FUNCTION(s)
	static void UpdateLightResource(ID3D11Buffer* lightBuffer, LightPropertiesConstantBuffer lightProp, ID3D11DeviceContext* context, ID3D11Device* device);
	static void UpdateLight(Camera* camera, LightObject* light, const float deltaTime, ID3D11DeviceContext* context, ID3D11Device* device, int index);
	static void DrawLight(LightObject light, ID3D11DeviceContext* context);


	// GETTER FUNCTION(s)
	Light GetLightData();

	inline XMFLOAT4 GetPosition() { return XMFLOAT4(m_Position); }
	float* GetPositionArray() { return m_Position; }

	inline XMFLOAT4 GetDirection() { return XMFLOAT4(m_Direction); }
	float* GetDirectionArray() { return m_Direction; }

	inline XMFLOAT4 GetColor() { return XMFLOAT4(m_Colour); }
	float* GetColorArray() { return m_Colour; }

	// SETTER FUNCTION(s)
	
	void SetLightData(LightObject* light);

	void SetPosition(float x, float y, float z, float w);
	void SetPosition(XMFLOAT4 position);

	void SetDirection(float x, float y, float z, float w);
	void SetDirection(XMFLOAT4 direction);

	void SetColor(float x, float y, float z, float w);
	void SetColor(XMFLOAT4 colour);

	inline void SetSpotAngle(float spotAngle) { m_Light.SpotAngle = spotAngle; }
	inline void SetConstantAttenuation(float constantAttenuation) { m_Light.ConstantAttenuation = constantAttenuation; }
	inline void SetLinearAttenuation(float linearAttenuation) { m_Light.LinearAttenuation = linearAttenuation; }
	inline void SetQuadraticAttenuation(float quadraticAttenuation) { m_Light.QuadraticAttenuation = quadraticAttenuation; }
	inline void SetLightType(int lightType) { m_Light.LightType = lightType; }
	inline void SetEnabled(int enabled) { m_Light.Enabled = enabled; }
};

#endif