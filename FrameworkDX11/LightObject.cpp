#include "LightObject.h"
#include "Camera.h"

LightObject::LightObject(ID3D11Device* device)
{
	for (int i = 0; i < 4; ++i)
	{
		m_Position[i] = 0;
		m_Colour[i] = 0;
		m_Direction[i] = 0;
	}

	// POSITION
	m_Light.Position.x = m_Position[0];
	m_Light.Position.y = m_Position[1];
	m_Light.Position.z = m_Position[2];
	m_Light.Position.w = m_Position[3];

	// DIRECTION
	m_Light.Direction.x = m_Direction[0];
	m_Light.Direction.y = m_Direction[1];
	m_Light.Direction.z = m_Direction[2];
	m_Light.Direction.w = m_Direction[3];

	// COLOR
	m_Light.Color.x = m_Colour[0];
	m_Light.Color.y = m_Colour[1];
	m_Light.Color.z = m_Colour[2];
	m_Light.Color.w = m_Colour[3];
}

LightObject::~LightObject()
{

}

void LightObject::UpdateLightResource(ID3D11Buffer* lightBuffer, LightPropertiesConstantBuffer lightProp, ID3D11DeviceContext* context, ID3D11Device* device)
{
	context->UpdateSubresource(lightBuffer, 0, nullptr, &lightProp, 0, 0);
}

void LightObject::DrawLight(LightObject light, ID3D11DeviceContext* context)
{
	
}

Light LightObject::GetLightData()
{
	Light t_TempLight;
	t_TempLight.Position = XMFLOAT4(m_Position);
	t_TempLight.Direction = XMFLOAT4(m_Direction);
	t_TempLight.Color = XMFLOAT4(m_Colour);

	t_TempLight.SpotAngle = m_Light.SpotAngle;
	t_TempLight.ConstantAttenuation = m_Light.ConstantAttenuation;
	t_TempLight.LinearAttenuation = m_Light.LinearAttenuation;
	t_TempLight.QuadraticAttenuation = m_Light.QuadraticAttenuation;
	t_TempLight.LightType = m_Light.LightType;
	t_TempLight.Enabled = m_Light.Enabled;

	return t_TempLight;
}

void LightObject::SetLightData(LightObject* light)
{
	for (int i = 0; i < 4; ++i)
	{
		m_Position[i] = light->GetPositionArray()[i];
		m_Direction[i] = light->GetDirectionArray()[i];
		m_Colour[i] = light->GetColorArray()[i];
	}

	m_Light.SpotAngle = light->GetLightData().SpotAngle;
	m_Light.ConstantAttenuation = light->GetLightData().ConstantAttenuation;
	m_Light.LinearAttenuation = light->GetLightData().LinearAttenuation;
	m_Light.QuadraticAttenuation = light->GetLightData().QuadraticAttenuation;
	m_Light.LightType = light->GetLightData().LightType;
	m_Light.Enabled = light->GetLightData().Enabled;
}

void LightObject::SetPosition(float x, float y, float z, float w)
{
	m_Light.Position = XMFLOAT4(x, y, z, w);

	m_Position[0] = x;
	m_Position[1] = y;
	m_Position[2] = z;
	m_Position[3] = w;
}

void LightObject::SetPosition(XMFLOAT4 position)
{
	m_Light.Position = position;

	m_Position[0] = position.x;
	m_Position[1] = position.y;
	m_Position[2] = position.z;
	m_Position[3] = position.w;
}

void LightObject::SetDirection(float x, float y, float z, float w)
{
	m_Direction[0] = x;
	m_Direction[1] = y;
	m_Direction[2] = z;
	m_Direction[3] = w;
}

void LightObject::SetDirection(XMFLOAT4 direction)
{
	m_Direction[0] = direction.x;
	m_Direction[1] = direction.y;
	m_Direction[2] = direction.z;
	m_Direction[3] = direction.w;
}

void LightObject::SetColor(float x, float y, float z, float w)
{
	m_Colour[0] = x;
	m_Colour[1] = y;
	m_Colour[2] = z;
	m_Colour[3] = w;
}

void LightObject::SetColor(XMFLOAT4 colour)
{
	m_Light.Color = colour;

	m_Colour[0] = colour.x;
	m_Colour[1] = colour.y;
	m_Colour[2] = colour.z;
	m_Colour[3] = colour.w;
}
