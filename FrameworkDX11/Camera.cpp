#include "Camera.h"

Camera::Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, int windowWidth, int windowHeight, int nearDepth, int farDepth)
	: m_Eye(position), m_At(at), m_Up(up), m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_NearDepth(nearDepth), m_FarDepth(farDepth)
{
	m_World = new XMFLOAT4X4();

	m_Speed = 5.0f;
	m_RotationSpeed = 5.f;

	m_ForwardVector = XMFLOAT3(0.0f, 0.0f, 1.0f);

	// Set View Matrix
	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixLookToLH(XMLoadFloat3(&m_Eye), XMLoadFloat3(&m_ForwardVector), XMLoadFloat3(&m_Up)));

	// Set Projection Matrix
	XMMATRIX TempMat;
	float t_Aspect = m_WindowWidth / m_WindowHeight;
	TempMat = XMMatrixPerspectiveFovLH(XMConvertToRadians(90), t_Aspect, 0.01, 100.0f);
	XMStoreFloat4x4(&m_ProjectionMatrix, TempMat);
}

Camera::~Camera()
{
	if (m_World != nullptr)
	{
		delete m_World;
		m_World = nullptr;
	}
}

void Camera::Update(const float deltaTime)
{
	// Getting the Inverse View Matrix
	XMMATRIX t_TempWorld = XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_ViewMatrix));

	// MOVEMENT
	if (GetAsyncKeyState(VK_W)) { t_TempWorld.r[3] += t_TempWorld.r[2] * m_Speed * deltaTime; } // Move Forward
	if (GetAsyncKeyState(VK_A)) { t_TempWorld.r[3] -= t_TempWorld.r[0] * m_Speed * deltaTime; } // Move Left
	if (GetAsyncKeyState(VK_S)) { t_TempWorld.r[3] -= t_TempWorld.r[2] * m_Speed * deltaTime; } // Move Back
	if (GetAsyncKeyState(VK_D)) { t_TempWorld.r[3] += t_TempWorld.r[0] * m_Speed * deltaTime; } // Move Right

	// UP AND DOWN
	if (GetAsyncKeyState(VK_E)) { t_TempWorld.r[3] += t_TempWorld.r[1] * m_Speed * deltaTime; } // Move Up
	if (GetAsyncKeyState(VK_Q)) { t_TempWorld.r[3] -= t_TempWorld.r[1] * m_Speed * deltaTime; } // Move Down


	// ROTATE (Left and Right) (Yaw)
	if (GetAsyncKeyState(VK_LEFT)) // Rotate Left
	{
		XMMATRIX CamRotation = XMMatrixRotationAxis(t_TempWorld.r[1], XMConvertToRadians(-1 * (m_RotationSpeed * 10) * deltaTime));
		t_TempWorld.r[0] = XMVector3TransformNormal(t_TempWorld.r[0], CamRotation);
		t_TempWorld.r[2] = XMVector3TransformNormal(t_TempWorld.r[2], CamRotation);
	}
	if (GetAsyncKeyState(VK_RIGHT)) // Rotate Right
	{
		XMMATRIX CamRotation = XMMatrixRotationAxis(t_TempWorld.r[1], XMConvertToRadians(1 * (m_RotationSpeed * 10) * deltaTime));
		t_TempWorld.r[0] = XMVector3TransformNormal(t_TempWorld.r[0], CamRotation);
		t_TempWorld.r[2] = XMVector3TransformNormal(t_TempWorld.r[2], CamRotation);
	}

	// ROTATE (Up and Down) (Pitch)
	if (GetAsyncKeyState(VK_UP)) // Rotate Up
	{
		XMMATRIX CamRotation = XMMatrixRotationAxis(t_TempWorld.r[0], XMConvertToRadians(-1 * (m_RotationSpeed * 10) * deltaTime));
		t_TempWorld.r[1] = XMVector3TransformNormal(t_TempWorld.r[1], CamRotation);
		t_TempWorld.r[2] = XMVector3TransformNormal(t_TempWorld.r[2], CamRotation);
	}
	if (GetAsyncKeyState(VK_DOWN)) // Rotate Down
	{
		XMMATRIX CamRotation = XMMatrixRotationAxis(t_TempWorld.r[0], XMConvertToRadians(1 * (m_RotationSpeed * 10) * deltaTime));
		t_TempWorld.r[1] = XMVector3TransformNormal(t_TempWorld.r[1], CamRotation);
		t_TempWorld.r[2] = XMVector3TransformNormal(t_TempWorld.r[2], CamRotation);
	}

	// ROTATE (ClockWise and Anti-Clockwise) (Roll)
	if (GetAsyncKeyState(VK_Z)) // Rotate Anit-Clockwise
	{
		XMMATRIX CamRotation = XMMatrixRotationAxis(t_TempWorld.r[2], XMConvertToRadians(1 * (m_RotationSpeed * 10) * deltaTime));
		t_TempWorld.r[0] = XMVector3TransformNormal(t_TempWorld.r[0], CamRotation);
		t_TempWorld.r[1] = XMVector3TransformNormal(t_TempWorld.r[1], CamRotation);
	}
	if (GetAsyncKeyState(VK_X)) // Rotate Clockwise
	{
		XMMATRIX CamRotation = XMMatrixRotationAxis(t_TempWorld.r[2], XMConvertToRadians(-1 * (m_RotationSpeed * 10) * deltaTime));
		t_TempWorld.r[0] = XMVector3TransformNormal(t_TempWorld.r[0], CamRotation);
		t_TempWorld.r[1] = XMVector3TransformNormal(t_TempWorld.r[1], CamRotation);
	}

	XMStoreFloat4x4(m_World, t_TempWorld);
	XMMATRIX t_TempView = XMMatrixInverse(nullptr, XMLoadFloat4x4(m_World));
	XMStoreFloat4x4(&m_ViewMatrix, t_TempView);
}

void Camera::SetCameraPosition(float x, float y, float z)
{
	XMMATRIX TempWorld = XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_ViewMatrix));

	TempWorld.r[3] += TempWorld.r[0] * x;
	TempWorld.r[3] += TempWorld.r[1] * y;
	TempWorld.r[3] += TempWorld.r[2] * z;

	XMStoreFloat4x4(m_World, TempWorld);
	XMMATRIX TempView = XMMatrixInverse(nullptr, XMLoadFloat4x4(m_World));
	XMStoreFloat4x4(&m_ViewMatrix, TempView);

	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixLookAtLH(XMLoadFloat3(&m_Eye), XMLoadFloat3(&m_At), XMLoadFloat3(&m_Up))); // Set AT needs this for the view matrix
}

void Camera::Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_NearDepth = nearDepth;
	m_FarDepth = farDepth;
}

XMMATRIX& Camera::GetCameraMatrix()
{
	XMMATRIX t_TempMat = XMLoadFloat4x4(m_World);
	return t_TempMat;
}
