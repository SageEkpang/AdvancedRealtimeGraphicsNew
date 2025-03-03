#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "structures.h"
#include "constants.h"

class Component
{
protected:
	
	Tag m_Tag;

public:

	// CLASS FUNCTION(s)
	Component(Tag tag, ID3D11Device* device) : m_Tag(tag) { }
	virtual ~Component() { };

	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime) = 0;
	virtual void Draw(ID3D11DeviceContext* context) = 0;

	// GETTER FUNCTION(s)
	inline Tag GetTag() { return m_Tag; }

	// SETTER FUNCTION(s)
	void SetTag(Tag tag) { m_Tag = tag; }
};

#endif