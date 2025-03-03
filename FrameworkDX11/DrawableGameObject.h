#pragma once
#ifndef DRAWWABLE_GAME_OBJECT_H
#define DRAWWABLE_GAME_OBJECT_H

// NEEDED INCLUDE(s)
#include "structures.h"
#include "constants.h"

// COMPONENT INCLUDE(s)
#include "Component.h"
#include "Transform.h"
#include "Render.h"
#include "Mesh.h"

// SHADER INCLUDE(s)
#include "Shader.h"

// COMPONENT DEFINE(s)
#define MAX_COMPONENTS 10

class DrawableGameObject
{
private:

	std::string m_Name;
	Transform* m_TransformComponent;
	Render* m_RenderComponent;
	Mesh* m_MeshComponent;

	// TODO: Change to Array Variable
	std::array<Component*, MAX_COMPONENTS> m_Components;

public:

	// CLASS FUNCTION(s)
	DrawableGameObject(std::string name);
	~DrawableGameObject();

	// BASE FUNCTION(s)
	void update(float t, ID3D11DeviceContext* context);
	void draw(ID3D11DeviceContext* context);

	// GETTER FUNCTION(s)
	inline std::string GetName() { return m_Name; }
	inline Transform* GetTransformComponent() { return m_TransformComponent; }
	inline Mesh* GetMeshComponent() { return m_MeshComponent; }
	inline Render* GetRenderComponent() { return m_RenderComponent; }

	// SETTER FUNCTION(s)
	void AddComponent(Component* component);

	inline void SetTransformComponent(Transform* transform) { m_TransformComponent = transform; }
	inline void SetMeshComponent(Mesh* mesh) { m_MeshComponent = mesh; }
	inline void SetRenderComponent(Render* render) { m_RenderComponent = render; }
};

#endif
