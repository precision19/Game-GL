#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	m_Name = "Object";
	m_Renderer = NULL;
}

Object::Object(string name)
{
	m_Name = name;
	m_Renderer = NULL;
}

Object* Object::Clone()
{
	Object* result = new Object();

	result->m_Name = m_Name;
	result->m_Transform = m_Transform;
	result->m_Renderer = m_Renderer->Clone();

	return result;
}

void Object::Reset()
{
	m_Transform.Reset();
	m_Renderer->Reset();
}

//void Object::SetNativeSize()
//{
//	m_Dimension = Vector2(m_Renderer->GetTextureSize().x * m_Transform.scale.x, m_Renderer->GetTextureSize().y * m_Transform.scale.y);
//}

void Object::SetPosition(Vector3 position)
{
	m_Transform.position = position;
}

string Object::GetName()
{
	return m_Name;
}

Vector3 Object::GetPosition()
{
	return m_Transform.position;
}

Renderer* Object::GetRenderere()
{
	return m_Renderer;
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

void Object::SetRenderer(string name)
{
	m_Renderer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
}

Renderer* Object::GetRenderer() {
	if (m_Renderer) return m_Renderer;
	else {
		printf("NULL RENDERER\n");
		return NULL;
	}
}

void Object::Draw()
{
	if (m_Renderer == NULL)
		printf("WARNING: object %s have no renderer", m_Name.c_str());
	else
		m_Renderer->Draw(m_Transform);
}

void Object::Update(float deltaTime)
{
	if (m_Renderer == NULL)
		printf("WARNING: object %s have no renderer", m_Name.c_str());
	else
		m_Renderer->Update(deltaTime);
}

Object::~Object()
{	
	if (m_Renderer != NULL) {
		delete m_Renderer;
		m_Renderer = NULL;
	}
}
