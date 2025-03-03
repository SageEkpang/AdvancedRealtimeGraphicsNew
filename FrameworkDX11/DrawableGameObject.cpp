#include "DrawableGameObject.h"

DrawableGameObject::DrawableGameObject(std::string name)
{
	m_Name = name;
	m_TransformComponent = nullptr;
	m_RenderComponent = nullptr;
	m_MeshComponent = nullptr;

	for (int i = 0; i < MAX_COMPONENTS; ++i) { m_Components[i] = nullptr; }
}

DrawableGameObject::~DrawableGameObject()
{
	if (m_TransformComponent != nullptr) delete m_TransformComponent;
	if (m_RenderComponent != nullptr) delete m_RenderComponent;
	if (m_MeshComponent != nullptr) delete m_MeshComponent;
}

void DrawableGameObject::update(float deltaTime, ID3D11DeviceContext* context)
{
	m_TransformComponent->Update(deltaTime);
	m_RenderComponent->Update(deltaTime);
	m_MeshComponent->Update(deltaTime);
}

void DrawableGameObject::draw(ID3D11DeviceContext* context)
{
	m_TransformComponent->Draw(context);
	m_RenderComponent->Draw(context);
	m_MeshComponent->Draw(context);
}

void DrawableGameObject::AddComponent(Component* component)
{
	if (m_Components.empty()) return;

	for (int i = 0; i < MAX_COMPONENTS; ++i)
	{
		if (m_Components[i] == nullptr)
		{
			m_Components[i] = component;
			return;
		}
	}

	std::cout << "No More Components can be added" << std::endl;
}
