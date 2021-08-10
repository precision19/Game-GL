#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

void Object::SetNativeSize()
{
	Vector3 size = m_Renderer->GetSize();
	m_Dimension = Vector2(size.x, size.y);
}

void Object::SetPosition(Vector3 position)
{
	transform.position = position;
}

Vector3 Object::GetPosition() 
{
	return transform.position;
}

void Object::SetScale(Vector3 scale)
{
	transform.scale = scale;
}

void Object::SetRotation(Vector3 rotation)
{
	transform.rotation = rotation * PI / 180;
}

void Object::SetRenderer(int id)
{
	m_Renderer = PrefabManager::GetInstance()->GetRenderer(id);
	m_Renderer->SetTransform(&transform);
}

void Object::Draw()
{
	m_Renderer->Draw();
}

void Object::Update(float deltaTime)
{
	m_Renderer->Update(deltaTime);
}

Object::~Object()
{
	delete m_Renderer;
	m_Renderer = NULL;
}
