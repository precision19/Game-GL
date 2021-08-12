#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	m_Name = "GameObject";
	ID = -1;
}

Object::Object(string name)
{
	m_Name = name;
}

Object* Object::Clone()
{
	Object* result = new Object();

	result->m_Name = m_Name;
	result->m_Dimension = m_Dimension;
	result->m_Transform = m_Transform;
	result->m_Renderer = m_Renderer->Clone();

	return result;
}

void Object::SetNativeSize(int k)
{
	m_Dimension = Vector2(m_Renderer->GetTextureSize().x * m_Transform.scale.x, m_Renderer->GetTextureSize().y * m_Transform.scale.y);
}

void Object::SetPosition(Vector3 position)
{
	m_Transform.position = position;
}

Vector3 Object::GetPosition() 
{
	return m_Transform.position;
}

void Object::SetScale(Vector3 scale)
{
	m_Transform.scale = scale;
}

void Object::SetRotation(Vector3 rotation)
{
	m_Transform.rotation = rotation * PI / 180;
}

void Object::SetRenderer(int id)
{
	m_Renderer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
}

void Object::Draw()
{
	m_Renderer->Draw(m_Transform);
}

void Object::Update(float deltaTime)
{
	m_Renderer->Update(deltaTime);
}

Object::~Object()
{
	delete m_Renderer;
}
